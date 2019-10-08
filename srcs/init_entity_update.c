/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:15:07 by jaelee            #+#    #+#             */
/*   Updated: 2019/10/08 16:21:26 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	entity_render_init(t_entity_render_info *info, t_s32 view,
			t_items *item)
{
	t_s32	sprite_pos_screen;

	info->offset.x = 0;
	info->sprite_size = abs((t_s32)((t_f32)H / item->transformed_sprite_pos.y));
	info->sprite_width_scale = (item->tex->width << 16) / info->sprite_size;
	sprite_pos_screen = (t_s32)(((t_f32)W) *
		(1.0f + item->transformed_sprite_pos.x /
			item->transformed_sprite_pos.y));
	info->draw_start.x = (-info->sprite_size + sprite_pos_screen) >> 1;
	info->draw_end.x = (info->sprite_size + sprite_pos_screen) >> 1;
	info->draw_start.y = ((-info->sprite_size + H) >> 1) - view;
	info->draw_end.y = ((info->sprite_size + H) >> 1) - view;
	if (info->draw_start.x < 0)
	{
		info->offset.x = info->draw_start.x;
		info->draw_start.x = 0;
	}
	if (info->draw_end.x >= W)
		info->draw_end.x = W - 1;
	if (info->draw_start.y < 0)
		info->draw_start.y = 0;
	if (info->draw_end.y >= H)
		info->draw_end.y = H - 1;
}

void	entity_render_setup(t_items *item, t_s32 view,
			t_entity_render_info *info)
{
	t_s32	sprite_pos;

	entity_render_init(info, view, item);
	sprite_pos = (info->draw_start.x + info->offset.x + info->draw_end.x) >> 1;
	if (sprite_pos < (W >> 1) + (info->sprite_size >> 2)
		&& sprite_pos > (W >> 1) - (info->sprite_size >> 2))
		item->flag |= 1UL;
	else
		item->flag &= ~1UL;
	info->offset.x += info->draw_start.x;
	info->offset.y = info->sprite_size - H;
}