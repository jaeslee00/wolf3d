/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:55:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/09 17:48:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//TODO (jae) : need a condition to call draw_enemy() for only those are within the player's view for optimization

void	image_fill(uint32 *img, f32 *perp_dist, t_texture *tex, t_items *item,
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
	sint32 tex_sprite_scale_x = (tex->width << 16) / sprite_width;
	
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
			tex_x[0] = (tex_width_scale[0] * tex_sprite_scale_x) >> 16;
			tex_x[1] = (tex_width_scale[1] * tex_sprite_scale_x) >> 16;
			tex_x[2] = (tex_width_scale[2] * tex_sprite_scale_x) >> 16;
			tex_x[3] = (tex_width_scale[3] * tex_sprite_scale_x) >> 16;
			taxi[0] = tex_x[0] + tex_y;
			taxi[1] = tex_x[1] + tex_y;
			taxi[2] = tex_x[2] + tex_y;
			taxi[3] = tex_x[3] + tex_y;
			if (item->transformed_sprite_pos.y < perp_dist[x]) 
			{
				if ((color[0] = tex->data[taxi[0]]) != TEXTURE_BLANK)
					img[x + img_y] = lighting(color[0], item->transformed_sprite_pos.y);
				if ((color[1] = tex->data[taxi[1]]) != TEXTURE_BLANK)
					img[x+1 + img_y] = lighting(color[1], item->transformed_sprite_pos.y);
				if ((color[2] = tex->data[taxi[2]]) != TEXTURE_BLANK)
					img[x+2 + img_y] = lighting(color[2], item->transformed_sprite_pos.y);
				if ((color[3] = tex->data[taxi[3]]) != TEXTURE_BLANK)
					img[x+3 + img_y] = lighting(color[3], item->transformed_sprite_pos.y);
			}
			x += 4;
		}
		y++;
	}
}

void	entity_draw(t_items *item, t_texture *tex, sint32 view, uint32 *img, f32 *perp_dist)
{
	sint32 sprite_height = abs((sint32)((f32)H / item->transformed_sprite_pos.y));
	sint32 sprite_width = sprite_height;
	sint32 sprite_pos_screen = (sint32)(((f32)W) * (1.0f + item->transformed_sprite_pos.x / item->transformed_sprite_pos.y));

	t_2d_p draw_start;
	t_2d_p draw_end;

	draw_start.x = (-sprite_width + sprite_pos_screen) >> 1;
	draw_end.x = (sprite_width + sprite_pos_screen) >> 1;
	draw_start.y = ((-sprite_height + H) >> 1) - view;
	draw_end.y = ((sprite_height + H) >> 1) - view;

	sint32 x_offset = 0;

	if (draw_start.x < 0)
	{
		x_offset = draw_start.x;
		draw_start.x = 0;
	}
if (draw_end.x >= W)
		draw_end.x = W - 1;

if (draw_start.y < 0)
draw_start.y = 0;
	if (draw_end.y >= H)
		draw_end.y = H - 1;
	if ((draw_start.x + draw_end.x) / 2 < W / 2 + ENEMY_SIZE
		&& (draw_start.x + draw_end.x) / 2 > W / 2 - ENEMY_SIZE)
item->flag |= 1UL;
else
		item->flag &= ~1UL;

	if (draw_start.x >= W || draw_end.x < 0 || draw_start.y >= H || draw_end.y < 0)
		return ;
	image_fill(img, perp_dist, tex, item, draw_start, draw_end, view, sprite_height, sprite_width, x_offset);
}

void	entity_draw_loop(t_wolf *wf, t_entity *entity, t_items *item, sint32 *order)
{
	sint32		index;

	index = 0;
while (index < entity->nbr_of_entities)
	{	
		if (item[order[index]].transformed_sprite_pos.y > 0.0f)
			entity_draw(&item[order[index]], item[order[index]].tex,
				wf->view, wf->img, wf->perp_dist);
index++;
	}
}
