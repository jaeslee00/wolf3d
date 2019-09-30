/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:18:48 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/01 20:18:48 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_crosshair(t_wolf *wolf)
{
	t_u32	i;
	t_u32	j;
	t_u32	k;

	i = (W / 2) - (5 * wolf->a.size);
	j = (H / 2);
	k = 0;
	while (k <= 10 * wolf->a.size)
	{
		wolf->img[i + j * W] = rgb_lerp(wolf->img[i + j * W] - 0xFFFF00, 0.2f,
										0xFFFF00);
		i++;
		k++;
	}
	i = (W / 2);
	j = (H / 2) - (5 * wolf->a.size);
	k = 0;
	while (k <= 10 * wolf->a.size)
	{
		if (j != (H / 2))
			wolf->img[i + j * W] = rgb_lerp(wolf->img[i + j * W] - 0xFFFF00,
											0.2f, 0xFFFF00) - 0x0000FF;
		j++;
		k++;
	}
}

void	draw_machinegun(t_wolf *wolf)
{
	if (wolf->flag & 1UL << 9)
	{
		wolf->a.gun += wolf->deltatime;
		if(wolf->a.gun < (t_s32)wolf->a.frame)
		{
			for (int i=0; i < wolf->entity->nbr_of_entities; i++)
				if (wolf->entity->item[i].flag & 1UL)
			{
				wolf->entity->item[i].flag |= 1UL << 1;
				wolf->entity->item[i].tex = &wolf->tex[13];
			}
			wolf->view -= wolf->deltatime / 2;
			draw_gun(wolf, 11);
		}
		else
		{
			wolf->view -= 1;
			draw_gun(wolf, 10);
			wolf->a.frame += 50;
		}
		if (wolf->a.gun >= 500)
		{
			draw_gun(wolf, 11);
			wolf->flag &= ~(1UL << 9);
			wolf->a.gun = 0;
		}
	}
	else
	{
		for (int i=0; i < wolf->entity->nbr_of_entities; i++)
		{
			wolf->entity->item[i].flag |= 1UL << 1;
			wolf->entity->item[i].tex = &wolf->tex[12];
		}
		wolf->a.frame = 0;
		draw_gun(wolf, 10);
	}
	if(wolf->view < -H / 2)
		wolf->view = -H / 2;
}
