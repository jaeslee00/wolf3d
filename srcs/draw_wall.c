/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:57:14 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/08 05:33:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

sint32	lighting(sint32 color, f32 distance)
{
	f32		light;

	if (distance < 3)
		return (color);
	else
		light = (1.0 - distance / 12.0);
	if (light < 0.0)
		light = 0.0;
	if (light > 1.0)
		light = 1.0;
	return (rgb_lerp(0.0, light + 0.19f, color));
}

sint8	texture_pick(t_raycaster *ray)
{
	if (ray->side == 0)
		return (ray->step.x < 0 ? TEXTURE_0 : TEXTURE_1);
	else if (ray->side == 1)
		return (ray->step.y < 0 ? TEXTURE_2 : TEXTURE_3);
	else
		return (TEXTURE_4);
}

void	texture_map(t_wolf *wf, t_texture_map *tex_map, sint32 x,
				t_raycaster *ray, t_texture *tex)
{
	sint32	tex_height_scale;
	sint32	color;
	sint32	tex_y;
	sint32	y_offset;
	sint32	y;
	(void)ray;
	y_offset = ((tex_map->column_height - H) >> 1) + wf->view;
	y = tex_map->start;
	while (y < tex_map->end)
	{
		tex_height_scale = y + y_offset;
		//TODO (jae) : "tex->height) / tex_map.column_height" might be pulled out from the loop
		tex_y = (tex_height_scale * tex->height) / tex_map->column_height;
		color = tex->data[tex->width * tex_y + tex_map->coord.x];
		//NOTE (jae) : lighting in ray_casting seems quite expensive. Needs to check!!
		wf->img[x + y * W] = lighting(color, ray->perp_dist);
		y += 1;
	}
}

void	draw_wall(t_wolf *wf, sint32 line_height, sint32 x, t_raycaster *ray)
{
	t_texture_map	tex_map;
	f32				tex_width_scale;
	sint32			tex_id;

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
	tex_map.coord.x = (sint32)(tex_width_scale * (f32)wf->tex[(sint32)texture_pick(ray)].width);
	texture_map(wf, &tex_map, x, ray, &wf->tex[tex_id]);
}
