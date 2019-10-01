/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:16:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/28 23:00:57 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_palette	ceiling(t_wolf *wolf)
{
	t_palette	p;
	t_s32	y;
	t_f32		per;

	ft_bzero(&p, sizeof(p));
	is_alloc(p.pal = ft_mem(&wolf->mem, sizeof(t_s32) * H / 2), wolf, -1);
	per = 0.5f;
	y = 0;
	while (y < H / 2)
	{
		p.pal[y] = rgb_lerp(0x0, per, 0xFFFFFF);
		y++;
		per -= 0.0009f;
	}
	p.size = y;
	return (p);
}

void		background(t_wolf *wolf, t_u32 *img)
{
	t_2d_p	coord;
	t_s32		i;
	t_palette	p;
	t_s32		y1;

	p = ceiling(wolf);
	i = ft_abs(wolf->view);
	coord.y = 0;
	y1 = H - 1;
	while (coord.y < H / 2)
	{
		coord.x = 0;
		while (coord.x < W - 1)
		{
			img[coord.x + coord.y * W] = p.pal[i];
			img[coord.x + y1 * W] = p.pal[i];
			coord.x++;
		}
		if (i < (t_s32)p.size)
			i++;
		coord.y++;
		y1--;
	}
	//printf("iter.x= %d, %d %d\n", iter.x, wolf->view, p.size);
}

// TODO(viccarau): In order to create the pallete, we can calculate the H * 2,
// then the middle point is where the pallete starts to draw
