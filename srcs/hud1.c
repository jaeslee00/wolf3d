/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:18:48 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 20:06:25 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		color_picker(t_wolf *wolf, t_s32 nb, t_s32 nb1, t_2d_p xy)
{
	if (nb == 4 || nb1 == 4)
		wolf->img[xy.x + (xy.y * W)] = 0x00BB00;
	else if (nb == 3 || nb1 == 3)
		wolf->img[xy.x + (xy.y * W)] = 0xBB0000;
	else if ((nb != 0 || nb1 != 0) && (nb != 9 && nb1 != 9))
		wolf->img[xy.x + (xy.y * W)] = 0x555555;
	else
		wolf->img[xy.x + (xy.y * W)] = 0x000000;
}

void		draw_crosshair(t_wolf *wolf)
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

static t_s8	draw_machine_anim(t_wolf *wolf)
{
	t_s8	i;

	i = 0;
	if ((i = (wolf->a.gun >= 500)))
	{
		change_sprite(wolf, 0, 11, 0);
		wolf->flag &= ~(1UL << 9);
		wolf->a.gun = 0;
	}
	else if ((i = (wolf->a.gun < (t_s32)wolf->a.frame)))
	{
		change_sprite(wolf, 13, 11, 1);
		wolf->view -= wolf->deltatime / 2;
	}
	return (i);
}

void		draw_machinegun(t_wolf *wolf)
{
	if (wolf->flag & 1UL << 9)
	{
		wolf->a.gun += wolf->deltatime;
		if (draw_machine_anim(wolf))
			;
		else
		{
			wolf->view -= 1;
			change_sprite(wolf, 0, 10, 0);
			wolf->a.frame += 50;
		}
	}
	else
	{
		change_sprite(wolf, 12, 10, 1);
		wolf->a.frame = 0;
	}
	if (wolf->view < -H / 2)
		wolf->view = -H / 2;
}
