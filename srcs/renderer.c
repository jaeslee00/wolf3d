/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:16:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/05 23:55:45 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_palette	ceiling(t_wolf *wolf)
{
	t_palette	p;
	t_s32		y;
	t_f32		per;
	t_f32		pix;

	ft_bzero(&p, sizeof(p));
	is_alloc(p.pal = ft_mem(&wolf->mem, sizeof(t_s32) * H / 2), wolf, -1);
	per = 0.5f;
	pix = 1.0f / (H);
	y = 0;
	while (y < H / 2)
	{
		p.pal[y] = rgb_lerp(0x0, per, 0xFF0000);
		y++;
		per -= pix;
	}
	p.size = y;
	return (p);
}

static void		down(t_wolf *wolf, t_u32 *img, t_2d_p coord, t_s32 i)
{
	while (coord.y < H)
	{
		coord.x = 0;
		while (coord.x < W - 1)
		{
			img[coord.x + coord.y * W] = wolf->background.pal[i];
			coord.x++;
		}
		if (i > 0)
			i--;
		coord.y++;
	}
}

static void		look_up_down(t_wolf *wolf, t_u32 *img)
{
	t_2d_p	coord;
	t_s32		i;
	
	i = wolf->view;
	coord.y = 0;
		while (coord.y < H / 2 - wolf->view)
		{
			coord.x = 0;
			while (coord.x < W - 1)
			{
				if (i < 0)
					img[coord.x + coord.y * W] = wolf->background.pal[0];
				else
					img[coord.x + coord.y * W] = wolf->background.pal[i];
				coord.x++;
			}
			if (i < (t_s32)wolf->background.size)
				i++;
			coord.y++;
		}
	down(wolf, img, coord, i);
		}

void			background(t_wolf *wolf, t_u32 *img)
{
	t_2d_p	coord;
	t_s32		i;
	t_s32		y1;

	coord.y = 0;
	y1 = H - 1;
	i = ft_abs(wolf->view);
	if (wolf->view == 0)
	{
		while (coord.y < H / 2 - wolf->view)
		{
			coord.x = 0;
			while (coord.x < W - 1)
			{
				img[coord.x + coord.y * W] = wolf->background.pal[i];
					img[coord.x + y1 * W] = wolf->background.pal[i];
				coord.x++;
			}
			if (i < (t_s32)wolf->background.size)
				i++;
			coord.y++;
			y1--;
		}
	}
else
		look_up_down(wolf, img);
}
