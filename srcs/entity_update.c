/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:55:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/05 23:21:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//TODO (jae) : need a condition to call draw_enemy() for only those are within the player's view for optimization

sint32	entity_update_status(t_entity *entity)
{
	if (entity->flag == 0b11)
		return (13);
	else
		return (12);
}

void entity_draw(t_entity *entity, t_texture *tex, sint32 view, uint32 *img, f32 *perp_dist)
{
	sint32 sprite_height = abs((sint32)((f32)H / entity->transformed_sprite_pos.y));
	sint32 sprite_width = sprite_height;
	sint32 sprite_pos_screen = (sint32)(((f32)W) * (1.0f + entity->transformed_sprite_pos.x / entity->transformed_sprite_pos.y));

	t_2d_p draw_start;
	t_2d_p draw_end;

	draw_start.x = -sprite_width / 2 + sprite_pos_screen / 2;
	draw_end.x = sprite_width / 2 + sprite_pos_screen / 2;
	//TODO (jae) : ENEMY_SIZE probably depends on resolution and DISTANCE from player!!!
	//TODO (jae) : After shooting, status of entity has to be independent i think..
	if ((draw_start.x + draw_end.x) / 2 < W / 2 + ENEMY_SIZE
		&& (draw_start.x + draw_end.x) / 2 > W / 2 - ENEMY_SIZE)
		entity->flag |= OBJ_VURNERABLE;
	else
		entity->flag = 0;
	sint32 x_offset = 0;
	if (draw_start.x < 0)
	{
		x_offset = draw_start.x;
		draw_start.x = 0;
	}
	else if (draw_start.x >= W)
		return ;
	if (draw_end.x >= W)
		draw_end.x = W - 1;
	else if (draw_end.x < 0)
		return ;

	draw_start.y = -sprite_height / 2 + H / 2 - view;
	draw_end.y = sprite_height / 2 + H / 2 - view;
	if (draw_start.y < 0)
		draw_start.y = 0;
	if (draw_end.y >= H)
		draw_end.y = H - 1;

	sint32 x;
	sint32 y;
	t_2d_p tex_coord;
	sint32 tex_width_scale;
	sint32 tex_height_scale;
	sint32 color;
	sint32	tex_id;
	sint32	taxi;
	if (entity->transformed_sprite_pos.y < 0)
		return ;

	tex_id = entity_update_status(entity);
	x = draw_start.x;
	printf("%d %d\n", draw_start.x, draw_end.x);
	while (x < draw_end.x)
	{
		tex_width_scale = x - draw_start.x - x_offset;
		tex_coord.x = tex_width_scale * tex[tex_id].width / sprite_width;
		y = draw_start.y;
		while (y < draw_end.y)
		{
			tex_height_scale = (y + view) * 2 - H + sprite_height;
			tex_coord.y =
				((tex_height_scale * tex[tex_id].height) / sprite_height) / 2;
			taxi = tex_coord.x + tex_coord.y * tex[tex_id].width;
			if ((entity->transformed_sprite_pos.y < perp_dist[x]))
			{
				if (tex[tex_id].data[taxi] != TEXTURE_BLANK)
				{
					color = tex[tex_id].data[taxi];
					img[x + y * W] = lighting(color, entity->transformed_sprite_pos.y);
				}
			}
			y++;
		}
		x++;
	}
}

void	entity_update(t_wolf *wf) //NOTE (jae) : Victor's function
{
	sint32		depth_buffer[NBR_OF_ENTITIES];
	f32			depth[NBR_OF_ENTITIES];
	sint32		index;

	sort_depth_buffer(wf, depth_buffer, depth);
	index = 0;
	while (index < NBR_OF_ENTITIES)
	{
		entity_draw(&wf->entity[depth_buffer[index]], wf->tex, wf->view, wf->img, wf->perp_dist);
		index++;
	}
}
