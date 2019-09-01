/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:19:22 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/31 17:35:57 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_bar(t_wolf *wolf, int percent)
{
	sint32	size;
	sint32	i;
	sint32	j;
	sint32	color;
	f32		norm;

	size = 250;
	i = W / 2 - size / 2;
	j = 100;
	norm = (f32)(percent * 0.01f);
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

void	draw_gun(t_wolf *wolf, uint32 tex_id)
{
	draw_sprite(wolf, init_2d((W / 2) - (wolf->tex[tex_id].width / 2) + 2,
		H - (wolf->tex[tex_id].height * wolf->a.size) + (2 * wolf->a.size)) ,
		wolf->tex[tex_id], wolf->a.size);
}

void	draw_shotgun(t_wolf *wolf, uint32 deltaframe)
{
	if (wolf->flag & 1UL << 9)
	{
		wolf->a.gun += deltaframe;
		if (wolf->a.gun < 100)
			draw_gun(wolf, 6);
		else if(wolf->a.gun < 150)
			draw_gun(wolf, 7);
		else
			draw_gun(wolf, 8);
		if (wolf->a.gun >= 400)
		{
			wolf->flag &= ~(1UL << 9);
			wolf->a.gun = 0;
		}
	}
	else
		draw_gun(wolf, 5);
}

void	draw_hud(t_wolf *wolf, uint32 deltaframe)
{
	if (wolf->flag & 1UL << 8)
		minimap(wolf);
	draw_bar(wolf, wolf->player.health);
	draw_shotgun(wolf, deltaframe);
}