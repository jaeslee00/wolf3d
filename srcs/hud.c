/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:19:22 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/09 17:42:49 by jaelee           ###   ########.fr       */
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

void	draw_gun(t_wolf *wolf, t_u32 tex_id)
{
	draw_sprite(wolf, init_2d((W / 2) - ((wolf->tex[tex_id].width * wolf->a.size) / 2) + 2,
		H - (wolf->tex[tex_id].height * wolf->a.size) + (2 * wolf->a.size)) ,
				wolf->tex[tex_id], wolf->a.size);
}

void	draw_shotgun(t_wolf *wolf, t_u32 deltaframe)
{
	if (wolf->flag & 1UL << 9)
	{
		wolf->a.gun += deltaframe;
		if (wolf->a.gun < 100)
		{
			for (int i=0; i < wolf->entity->nbr_of_entities; i++)
				if (wolf->entity->item[i].flag & 1UL)
			{
				wolf->entity->item[i].flag |= 1UL << 1;
				wolf->entity->item[i].tex = &wolf->tex[13];
			}
			draw_gun(wolf, 6);
		}
		else if(wolf->a.gun < 145)
		{
			wolf->view -= 10;
			draw_gun(wolf, 7);
		}
		else if (wolf->a.gun < 250)
			draw_gun(wolf, 9);
		else if (wolf->a.gun < 500)
		{
			for (int i=0; i < wolf->entity->nbr_of_entities; i++)
				wolf->entity->item[i].tex = &wolf->tex[12];
			draw_gun(wolf, 8);
		}
		else
			draw_gun(wolf, 9);
		if (wolf->a.gun >= 600)
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

void	draw_hud(t_wolf *wolf, t_u32 deltaframe)
{
	if (wolf->flag & 1UL << 8)
		minimap(wolf);
	draw_bar(wolf, wolf->player->health);
	if (wolf->flag & 1UL << 10)
		draw_shotgun(wolf, deltaframe);
	else
		draw_machinegun(wolf, deltaframe);
	draw_crosshair(wolf);
}
