/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:55:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/05 02:09:11 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//TODO (jae) : need a condition to call draw_enemy() for only those are within the player's view for optimization

void draw_entity(t_wolf *wf, t_entity *entity, t_texture *tex)
{
	sint32 sprite_height = abs((sint32)((f32)H / entity->transformed_sprite_pos.y));
	sint32 sprite_width = sprite_height;
	sint32 sprite_pos_screen = (sint32)(((f32)W) * (1.0f + entity->transformed_sprite_pos.x / entity->transformed_sprite_pos.y));

	t_2d_p draw_start;
	t_2d_p draw_end;

	draw_start.y = -sprite_height / 2 + H / 2 - wf->view;
	draw_end.y = sprite_height / 2 + H / 2 - wf->view;
	if (draw_start.y < 0)
		draw_start.y = 0;
	if (draw_end.y >= H)
		draw_end.y = H - 1;

	draw_start.x = -sprite_width / 2 + sprite_pos_screen / 2;
	draw_end.x = sprite_width / 2 + sprite_pos_screen / 2;
	//TODO (jae) : ENEMY_SIZE probably depends on resolution!
	if ((draw_start.x + draw_end.x) / 2 < W / 2 + ENEMY_SIZE
		&& (draw_start.x + draw_end.x) / 2 > W / 2 - ENEMY_SIZE)
		entity->flag |= OBJ_VURNERABLE;
	sint32 x_offset = 0;
	if (draw_start.x < 0)
	{
		x_offset = draw_start.x;
		draw_start.x = 0;
	}
	if (draw_end.x >= W)
		draw_end.x = W - 1;

	sint32 x;
	sint32 y;
	t_2d_p tex_coord;
	sint32 tex_width_scale;
	sint32 tex_height_scale;
	sint32 color;

	x = draw_start.x;
	while (x < draw_end.x)
	{
		tex_width_scale = x - draw_start.x - x_offset;
		tex_coord.x = tex_width_scale * tex->width / sprite_width;
		y = draw_start.y;
		while (y < draw_end.y)
		{
			tex_height_scale = (y + wf->view) * 2 - H + sprite_height;
			tex_coord.y =
				((tex_height_scale * tex->height) / sprite_height) / 2;
			if (entity->transformed_sprite_pos.y > 0 && (entity->transformed_sprite_pos.y < wf->perp_dist[x]))
			{
				if (tex->data[tex_coord.x + tex_coord.y * tex->width] != TEXTURE_BLANK)
				{
					color = tex->data[tex_coord.x + tex_coord.y * tex->width];
					wf->img[x + y * W] = lighting(color, entity->transformed_sprite_pos.y);
				}
			}
			y++;
		}
		x++;
	}
}

void	update_entity(t_wolf *wf) //NOTE (jae) : Victor's function
{
	sint32		tex_id = 12;
	sint32		depth_buffer[NBR_OF_ENTITIES];
	f32			depth[NBR_OF_ENTITIES];
	sint32		index;

	index = 0;
	sort_depth_buffer(wf, depth_buffer, depth);
	index = 0;
	while (index < NBR_OF_ENTITIES)
	{
		draw_entity(wf, &wf->entity[depth_buffer[index]], &wf->tex[tex_id]);
		index++;
	}
}
