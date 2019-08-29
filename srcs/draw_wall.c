/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:57:14 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/28 23:54:33 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

sint32	lighting(sint32 color, t_raycaster *ray)
{
	if (ray->perp_dist > 20)
		return (0);
	else if (ray->perp_dist > 10)
		ray->light = 0.2;
	else if (ray->perp_dist < 3)
		return (color);
	else
		ray->light = (1.0 - ray->perp_dist / 12.0);
	if (ray->light < 0.0)
		ray->light = 0.0;
	if (ray->light > 1.0)
		ray->light = 1.0;
	return (rgb_lerp(0.0, ray->light + 0.19f, color));
}

sint8	texture_pick(t_raycaster *ray)
{
	if (ray->side == EW_WALL)
		return (ray->step.x < 0 ? TEXTURE_0 : TEXTURE_1);
	else if (ray->side == SN_WALL)
		return (ray->step.y < 0 ? TEXTURE_2 : TEXTURE_3);
	else
		return (TEXTURE_4);
}

void	texture_map(t_wolf *wf, t_texture_map tex_map, sint32 x,
			t_raycaster *ray)
{
	sint32	tex_id;
	sint32	tex_height_scale;
	sint32	color;

	tex_id = texture_pick(ray);
	while (tex_map.start < tex_map.end)
	{
		tex_height_scale = tex_map.start * 2 - H + tex_map.column_height + 1;
		tex_map.coord.y =
			((tex_height_scale * TEX_WIDTH) / tex_map.column_height) / 2;
		color =
			wf->tex[tex_id].data[TEX_WIDTH * tex_map.coord.y + tex_map.coord.x];
		wf->img[x + tex_map.start * W] = lighting(color, ray);
		tex_map.start++;
	}
}

void	draw_wall(t_wolf *wf, sint32 line_height, sint32 x, t_raycaster *ray)
{
	t_texture_map	tex_map;
	f32				tex_width_scale;

	tex_map.start = -line_height / 2 + H / 2;
	tex_map.end = line_height / 2 + H / 2;
	tex_map.column_height = line_height;
	if (tex_map.start < 0)
		tex_map.start = 0;
	if (tex_map.end >= H)
		tex_map.end = H - 1;
	if (ray->side == EW_WALL || ray->side == 3)
		tex_width_scale = wf->player.pos.y + ray->perp_dist * wf->player.ray.y;
	else
		tex_width_scale = wf->player.pos.x + ray->perp_dist * wf->player.ray.x;
	tex_width_scale -= floor(tex_width_scale);
	tex_map.coord.x = (sint32)(tex_width_scale * (f32)TEX_WIDTH);
	texture_map(wf, tex_map, x, ray);
}
