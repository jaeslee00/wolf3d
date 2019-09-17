/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:55:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/17 16:52:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//TODO (jae) : need a condition to call draw_enemy() for only those are within the player's view for optimization

void	texel_scale(sint32 *texel, sint32 translatedx, sint32 sprite_width_scale, sint32 tex_y)
{
	sint32	tex_x[4];
	sint32	translated_x[4];

	translated_x[0] = translatedx;
	translated_x[1] = translatedx + 1;
	translated_x[2] = translatedx + 2;
	translated_x[3] = translatedx + 3;
	tex_x[0] = (translated_x[0] * sprite_width_scale) >> 16;
	tex_x[1] = (translated_x[1] * sprite_width_scale) >> 16;
	tex_x[2] = (translated_x[2] * sprite_width_scale) >> 16;
	tex_x[3] = (translated_x[3] * sprite_width_scale) >> 16;
	texel[0] = tex_x[0] + tex_y;
	texel[1] = tex_x[1] + tex_y;
	texel[2] = tex_x[2] + tex_y;
	texel[3] = tex_x[3] + tex_y;
}

void	draw_to_pixel(uint32 *img, uint32 *tex_data, sint32 *texel, f32 distance)
{
	sint32	color[4];

	if ((color[0] = tex_data[texel[0]]) != TEXTURE_BLANK)
		*img = lighting(color[0], distance);
	if ((color[1] = tex_data[texel[1]]) != TEXTURE_BLANK)
		*(img + 1) = lighting(color[1], distance);
	if ((color[2] = tex_data[texel[2]]) != TEXTURE_BLANK)
		*(img + 2) = lighting(color[2], distance);
	if ((color[3] = tex_data[texel[3]]) != TEXTURE_BLANK)
		*(img + 3) = lighting(color[3], distance);	
}

static t_2d_p	precalculate_offset(t_entity_render_info *info)
{
	t_2d_p	offset;

	offset.x = info->x_offset + info->draw_start.x;
	offset.y = info->sprite_size - H;

	return (offset);
}

//NOTE (jae) : can be troublesome if the size of the sprite is not multiple of 4
void	entity_render(uint32 *img, f32 *perp_dist, t_items *item, t_entity_render_info *info)
{
	t_2d_p		idx;
	sint32		tex_y;
	sint32		img_y;
	t_2d_p		translated;
	sint32		texel[4]; // texel[4] = img_y... it feels like shit to do this T-T
	t_2d_p		offset;

	offset = precalculate_offset(info);
	idx.y = info->draw_start.y + 1;
	while (idx.y < info->draw_end.y)
	{
		translated.y = ((idx.y + info->view) << 1) + offset.y;
		tex_y = (((translated.y * item->tex->height) / info->sprite_size) >> 1) * item->tex->width;
		img_y = idx.y * W;
		idx.x = info->draw_start.x;
		while (idx.x < info->draw_end.x - 3)
		{
			translated.x = idx.x - offset.x;
			texel_scale(texel, translated.x, info->sprite_width_scale, tex_y);
			if (item->transformed_sprite_pos.y < perp_dist[idx.x])
				draw_to_pixel(img + (idx.x + img_y), item->tex->data, texel, item->transformed_sprite_pos.y);
			idx.x += 4;
		}
		idx.y++;
	}
}

void	entity_render_init(t_entity_render_info *info, sint32 view, t_items *item)
{
	sint32	sprite_pos_screen;
	
	info->x_offset = 0;
	info->sprite_size = abs((sint32)((f32)H / item->transformed_sprite_pos.y));
	info->sprite_width_scale = (item->tex->width << 16) / info->sprite_size;
	sprite_pos_screen = (sint32)(((f32)W) *
		(1.0f + item->transformed_sprite_pos.x /
			item->transformed_sprite_pos.y));
	info->draw_start.x = (-info->sprite_size + sprite_pos_screen) >> 1;
	info->draw_end.x = (info->sprite_size + sprite_pos_screen) >> 1;
	info->draw_start.y = ((-info->sprite_size + H) >> 1) - view;
	info->draw_end.y = ((info->sprite_size + H) >> 1) - view;
	if (info->draw_start.x < 0)
	{
		info->x_offset = info->draw_start.x;
		info->draw_start.x = 0;
	}
	if (info->draw_end.x >= W)
		info->draw_end.x = W - 1;
	if (info->draw_start.y < 0)
		info->draw_start.y = 0;
	if (info->draw_end.y >= H)
		info->draw_end.y = H - 1;	
}

sint8	entity_render_setup(t_items *item, sint32 view, t_entity_render_info *info)
{
	sint32	sprite_horiz_pos;
	
	entity_render_init(info, view, item);
	sprite_horiz_pos = (info->draw_start.x + info->draw_end.x) >> 1;
	if (sprite_horiz_pos < (W >> 1) + (info->sprite_size >> 2)
		&& sprite_horiz_pos > (W >> 1) - (info->sprite_size >> 2))
		item->flag |= 1UL;
	else
		item->flag &= ~1UL;
	if (info->draw_start.x >= W || info->draw_end.x < 0 || info->draw_start.y >= H || info->draw_end.y < 0)
		return (-1);
	return (1);
}

void	entity_draw_loop(t_wolf *wf, t_items *item, sint32 *order, sint32 nbr_of_entities)
{
	sint32					index;
	t_entity_render_info	info;
	
	index = 0;
	info.view = wf->view;
	while (index < nbr_of_entities)
	{	
		if (item[order[index]].transformed_sprite_pos.y > 0.0f)
		{
			if (entity_render_setup(&item[order[index]], wf->view, &info) > 0)
				entity_render(wf->img, wf->perp_dist, &item[order[index]], &info);
		}
		index++;
	}
}
