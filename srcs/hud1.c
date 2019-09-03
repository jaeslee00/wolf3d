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

void	draw_machinegun(t_wolf *wolf, uint32 deltaframe)
{
	if (wolf->flag & 1UL << 9)
	{
		wolf->a.gun += deltaframe;
		if(wolf->a.gun < (sint32)wolf->a.frame)
		{
			wolf->view -= 1;
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
		wolf->a.frame = 0;
		draw_gun(wolf, 10);
	}
	if(wolf->view < -H / 2)
		wolf->view = -H / 2;
}
