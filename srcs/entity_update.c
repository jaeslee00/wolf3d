/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:55:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/08 01:48:48 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <pthread.h>

//TODO (jae) : need a condition to call draw_enemy() for only those are within the player's view for optimization

sint32	entity_update_status(t_entity *entity)
{
	if (entity->flag == 0b11)
		return (13);
	else
		return (12);
}

void	image_fill(uint32 *img, f32 *perp_dist, t_texture *tex, t_entity *entity,
			t_2d_p draw_start, t_2d_p draw_end, sint32 view, sint32 sprite_height,
				sint32 sprite_width, sint32 x_offset)
{
	sint32	x;
	sint32	y;
	t_2d_p	tex_coord;
	sint32	tex_x[4];
	sint32	tex_y;
	sint32	tex_width_scale[4];
	sint32	tex_height_scale;
	sint32	color[4];
	sint32	taxi[4];
	sint32	img_y;
	sint32	precalc_x;
	sint32 y_cam_pos;
	sint32	x_max = draw_end.x - 4;
	sint32 tex_sprite_scale_x = (tex->width << 8) / sprite_width;
	
	x_offset += draw_start.x;
	y = draw_start.y;
	y_cam_pos = sprite_height - H;
	while (y < draw_end.y)
	{
		tex_height_scale = ((y + view) << 1) + y_cam_pos;
		tex_coord.y =
			((tex_height_scale * tex->height) / sprite_height) >> 1;
		tex_y = tex_coord.y * tex->width;
		x = draw_start.x;
		img_y = y * W;
		while (x < x_max)
		{
			precalc_x = x - x_offset;
			tex_width_scale[0] = precalc_x;
			tex_width_scale[1] = precalc_x + 1;
			tex_width_scale[2] = precalc_x + 2;
			tex_width_scale[3] = precalc_x + 3;
			tex_x[0] = (tex_width_scale[0] * tex_sprite_scale_x) >> 8;
			tex_x[1] = (tex_width_scale[1] * tex_sprite_scale_x) >> 8;
			tex_x[2] = (tex_width_scale[2] * tex_sprite_scale_x) >> 8;
			tex_x[3] = (tex_width_scale[3] * tex_sprite_scale_x) >> 8;
			taxi[0] = tex_x[0] + tex_y;
			taxi[1] = tex_x[1] + tex_y;
			taxi[2] = tex_x[2] + tex_y;
			taxi[3] = tex_x[3] + tex_y;
			if (entity->transformed_sprite_pos.y < perp_dist[x]) 
			{
				if ((color[0] = tex->data[taxi[0]]) != TEXTURE_BLANK)
					img[x + img_y] = lighting(color[0], entity->transformed_sprite_pos.y);
				if ((color[1] = tex->data[taxi[1]]) != TEXTURE_BLANK)
					img[x+1 + img_y] = lighting(color[1], entity->transformed_sprite_pos.y);
				if ((color[2] = tex->data[taxi[2]]) != TEXTURE_BLANK)
					img[x+2 + img_y] = lighting(color[2], entity->transformed_sprite_pos.y);
				if ((color[3] = tex->data[taxi[3]]) != TEXTURE_BLANK)
					img[x+3 + img_y] = lighting(color[3], entity->transformed_sprite_pos.y);
			}
			x += 4;
		}
		y++;
	}
}

void	entity_draw(t_entity *entity, t_texture *tex, sint32 view, uint32 *img, f32 *perp_dist)
{
	sint32 sprite_height = abs((sint32)((f32)H / entity->transformed_sprite_pos.y));
	sint32 sprite_width = sprite_height;
	sint32 sprite_pos_screen = (sint32)(((f32)W) * (1.0f + entity->transformed_sprite_pos.x / entity->transformed_sprite_pos.y));

	t_2d_p draw_start;
	t_2d_p draw_end;
	sint32	tex_id;
	
	draw_start.x = (-sprite_width + sprite_pos_screen) >> 1;
	draw_end.x = (sprite_width + sprite_pos_screen) >> 1;

	sint32 x_offset = 0;
	if (draw_start.x < 0)
	{
		x_offset = draw_start.x;
		draw_start.x = 0;
	}
	if (draw_end.x >= W)
		draw_end.x = W - 1;
	if (draw_start.x >= W || draw_end.x < 0)
		return ;

	draw_start.y = ((-sprite_height + H) >> 1) - view;
	draw_end.y = ((sprite_height + H) >> 1) - view;
	if (draw_start.y < 0)
		draw_start.y = 0;
	if (draw_end.y >= H)
		draw_end.y = H - 1;

	if ((draw_start.x + draw_end.x) / 2 < W / 2 + ENEMY_SIZE
		&& (draw_start.x + draw_end.x) / 2 > W / 2 - ENEMY_SIZE)
		entity->flag |= OBJ_ON_TARGET;
	else
		entity->flag = 0;

	tex_id = entity_update_status(entity);
	image_fill(img, perp_dist, &tex[tex_id], entity, draw_start, draw_end, view, sprite_height, sprite_width, x_offset);
}

void	entity_update(t_wolf *wf)
{
	sint32		depth_buffer[NBR_OF_ENTITIES];
	f32			depth[NBR_OF_ENTITIES];
	sint32		index;

	sort_depth_buffer(wf, depth_buffer, depth);
	index = 0;
	while (index < NBR_OF_ENTITIES)
	{
		if (wf->entity[depth_buffer[index]].transformed_sprite_pos.y > 0.0f)
			entity_draw(&wf->entity[depth_buffer[index]], wf->tex, wf->view, wf->img, wf->perp_dist);
		index++;
	}
}
