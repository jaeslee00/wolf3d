/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:19:22 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/22 21:45:09 by viccarau         ###   ########.fr       */
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

void	draw_gun(t_wolf *wolf, t_u32 tex_id)
{
	draw_sprite(wolf, init_2d((W / 2) - ((wolf->tex[tex_id].width * wolf->a.size) / 2) + 2,
		H - (wolf->tex[tex_id].height * wolf->a.size) + (2 * wolf->a.size)) ,
				wolf->tex[tex_id], wolf->a.size);
}

static void	change_sprite(t_wolf *wolf, t_s32 idx, t_s32 gun, t_s32 update)
{
	t_s32	i;

	i = 0;
	if (gun == 7)
		wolf->view -= 10;
	if (update)
	{
		while (i < wolf->entity->nbr_of_entities)
		{
			if (wolf->entity->item[i].flag & 1UL)
			{
				wolf->entity->item[i].flag |= 1UL << 1;
				wolf->entity->item[i].tex = &wolf->tex[idx];
			}
			i++;
		}
	}
	draw_gun(wolf, gun);
}

void	draw_shotgun(t_wolf *wolf, t_u32 deltaframe)
{
	if (wolf->flag & 1UL << 9)
	{
		wolf->a.gun += deltaframe;
		if (wolf->a.gun < 50)
			change_sprite(wolf, 13, 6, 1);
		else if(wolf->a.gun < 100)
			change_sprite(wolf, 0, 7, 0);
		else if (wolf->a.gun < 150)
			change_sprite(wolf, 0, 9, 0);
		else if (wolf->a.gun < 250)
			change_sprite(wolf, 12, 8, 1);
		else
			change_sprite(wolf, 0, 9, 0);
		if (wolf->a.gun >= 300)
		{
			wolf->flag &= ~(1UL << 9);
			wolf->a.gun = 0;
		}
	}
	else
		draw_gun(wolf, 5);
	if(wolf->view < -H / 2)
		wolf->view = -H / 2;
}

void	draw_bar(t_wolf *wolf, int percent)
{
	t_s32	size;
	t_s32	i;
	t_s32	j;
	t_s32	color;
	t_f32		norm;

	size = 250;
	i = W / 2 - size / 2;
	j = 100;
	norm = (t_f32)(percent * 0.01f);
	percent = lerp(i, norm, size + (W / 2 - size / 2));
	while (j < (H / 10))
	{
		i = W / 2 - size / 2;
		color = 0x00FF00;
		while(i < (size + (W / 2 - size / 2)))
		{
			if (i == percent)
				color = 0xFF0000;
			wolf->img[i + W * j] = color;
			i++;
		}
		j++;
	}
}

void	draw_hud(t_wolf *wolf, t_u32 deltaframe)
{
	if (wolf->flag & 1UL << 8)
		draw_minimap(wolf);
	//draw_bar(wolf, wolf->player->health);
	if (wolf->flag & 1UL << 10)
		draw_shotgun(wolf, deltaframe);
	else
		draw_machinegun(wolf, deltaframe);
	draw_crosshair(wolf);
}
