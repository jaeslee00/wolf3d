/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:57:14 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/21 20:56:20 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_s32	lighting(t_s32 color, t_f32 distance)
{
	t_f32		light;

	if (distance < 3.0f)
		return (color);
	else
		light = (1.0f - distance / 12.0f);
	if (light < 0.0f)
		light = 0.0f;
	if (light > 1.0f)
		light = 1.0f;
	return (rgb_lerp(0, light + 0.19f, color));
}

t_s8	texture_pick(t_raycaster *ray)
{
	if (ray->side == 0)
		return (ray->step.x < 0 ? TEXTURE_0 : TEXTURE_1);
	else if (ray->side == 1)
		return (ray->step.y < 0 ? TEXTURE_2 : TEXTURE_3);
	else
		return (TEXTURE_4);
}

void	texture_map(t_wolf *wf, t_texture_map *tex_map, t_s32 x, t_f32 perp_dist,
			t_texture *tex)
{
t_s32	translated_y;
	t_s32	color;
	t_s32	tex_y;
	t_s32	y_offset;
	t_s32	y;
	t_s32 precalc;
	t_u32	*img = wf->img;
	
precalc = (tex->height << 24) / tex_map->column_height;
	y_offset = ((tex_map->column_height - H) >> 1) + wf->view;
	y = tex_map->start + 1;
	while (y < tex_map->end)
	{
		translated_y = y + y_offset;
		tex_y = ((translated_y * precalc) >> 24) * tex->width;
		color = tex->data[tex_y + tex_map->coord.x];
img[x + y * W] = lighting(color, perp_dist);
		y++;
	}
}

void	draw_wall(t_wolf *wf, t_s32 line_height, t_s32 x, t_raycaster *ray)
{
	t_texture_map	tex_map;
	t_f32				tex_width_scale;
	t_s32			tex_id;

	tex_id = texture_pick(ray);
	tex_map.start = ((-line_height + H) >> 1) - wf->view;
	tex_map.end = ((line_height + H) >> 1) - wf->view;
	tex_map.column_height = line_height;
	if (tex_map.start < 0)
		tex_map.start = 0;
	if (tex_map.end >= H)
		tex_map.end = H - 1;
	if (ray->side == 0 || ray->side == 3)
		tex_width_scale = wf->player->pos.y + ray->perp_dist * wf->player->ray.y;
	else
		tex_width_scale = wf->player->pos.x + ray->perp_dist * wf->player->ray.x;
	tex_width_scale -= floor(tex_width_scale);
	tex_map.coord.x = (t_s32)(tex_width_scale * (t_f32)wf->tex[(t_s32)texture_pick(ray)].width);
	//TODO (jae) : reverse texture when looking left
	texture_map(wf, &tex_map, x, ray->perp_dist, &wf->tex[tex_id]);
}
