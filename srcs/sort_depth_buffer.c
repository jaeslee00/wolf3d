/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_depth_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 01:40:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/05 02:11:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	swap_integer(sint32 *a, sint32 *b)
{
	sint32 tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_float(f32 *a, f32 *b)
{
	f32 tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

sint32	partition(sint32 *depth_buffer, f32 *depth, sint32 low, sint32 high)
{
	f32		pivot;
	sint32	i;
	sint32	j;

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

void	quick_sort(sint32 *depth_buffer, f32 *depth, sint32 low, sint32 high)
{
	sint32 pivot_idx;

	if (low < high)
	{
		pivot_idx = partition(depth_buffer, depth, low, high);
		quick_sort(depth_buffer, depth, low, pivot_idx - 1);
		quick_sort(depth_buffer, depth, pivot_idx + 1, high);
	}
}

void	sort_depth_buffer(t_wolf *wf, sint32 *depth_buffer, f32 *depth)
{
	sint32	index;
	t_2d	relative_entity_pos;
	f32		inv_det;

	index = 0;
	while (index < NBR_OF_ENTITIES)
	{
		relative_entity_pos.x = wf->entity[index].pos.x - wf->player.pos.x;
		relative_entity_pos.y = wf->entity[index].pos.y - wf->player.pos.y;
		inv_det = 1.0f / (wf->player.plane.x * wf->player.direction.y -
						  wf->player.plane.y * wf->player.direction.x);
		wf->entity[index].transformed_sprite_pos.x = inv_det *
			(wf->player.direction.y * relative_entity_pos.x -
				wf->player.direction.x * relative_entity_pos.y);
		wf->entity[index].transformed_sprite_pos.y = inv_det *
			(-wf->player.plane.y * relative_entity_pos.x +
				wf->player.plane.x * relative_entity_pos.y);
		depth_buffer[index] = index;
		depth[index] = wf->entity[index].transformed_sprite_pos.y;
		index++;
	}
	quick_sort(depth_buffer, depth, 0, NBR_OF_ENTITIES - 1);
}
