/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entity_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 01:40:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/09 18:06:00 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	swap_integer(t_s32 *a, t_s32 *b)
{
	t_s32 tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_float(t_f32 *a, t_f32 *b)
{
	t_f32 tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_s32	partition(t_s32 *depth_buffer, t_f32 *depth, t_s32 low, t_s32 high)
{
	t_f32		pivot;
	t_s32	i;
	t_s32	j;

	pivot = depth[high];
	i = (low - 1);
	j = low;
	while (j < high)
	{
		if (depth[j] >= pivot)
		{
			i++;
			swap_float(&depth[i], &depth[j]);
			swap_integer(&depth_buffer[i], &depth_buffer[j]);
		}
		j++;
	}
	swap_float(&depth[i + 1], &depth[high]);
	swap_integer(&depth_buffer[i + 1], &depth_buffer[high]);
	return (i + 1);
}

void	quick_sort(t_s32 *depth_buffer, t_f32 *depth, t_s32 low, t_s32 high)
{
	t_s32 pivot_idx;

	if (low < high)
	{
		pivot_idx = partition(depth_buffer, depth, low, high);
		quick_sort(depth_buffer, depth, low, pivot_idx - 1);
		quick_sort(depth_buffer, depth, pivot_idx + 1, high);
	}
}

void	sort_depth_buffer(t_entity *entity, t_items *item, t_player *player)
{
	t_s32	index;
	t_2d	relative_entity_pos;
	t_f32		inv_det;

	index = 0;
	while (index < entity->nbr_of_entities)
	{
		relative_entity_pos.x = item[index].pos.x - player->pos.x;
		relative_entity_pos.y = item[index].pos.y - player->pos.y;
		inv_det = 1.0f / (player->plane.x * player->direction.y -
			player->plane.y * player->direction.x);
		item[index].transformed_sprite_pos.x = inv_det *
			(player->direction.y * relative_entity_pos.x -
				player->direction.x * relative_entity_pos.y);
		item[index].transformed_sprite_pos.y = inv_det *
			(-player->plane.y * relative_entity_pos.x +
				player->plane.x * relative_entity_pos.y);
		entity->order[index] = index;
		entity->depth[index] = item[index].transformed_sprite_pos.y;
		index++;
	}
	quick_sort(entity->order, entity->depth, 0, entity->nbr_of_entities - 1);
}
