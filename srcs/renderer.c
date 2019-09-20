/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:16:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/01 13:18:39 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_palette	ceiling(void)
{
	t_palette	p;
	t_s32	y;
	t_f32		per;

	ft_bzero(&p, sizeof(p));
	p.palete = ft_memalloc(sizeof(t_s32) * H / 2);
	per = 2.71f;
	y = 0;
	while (y < H / 2)
	{
		p.palete[y] = rgb_lerp(0x111111, per, 0x222222);
		y++;
		per -= 0.01f;
	}
	p.size = y;
	//printf("sizeof(pal) = %d\n", p.size);
	return (p);
}

void		background(t_wolf *wolf, t_u32 *img)
{
	t_2d_p	coord;
	t_2d_p	iter;
	t_u32	y1;
	t_palette	p;

	p = ceiling();
	(void)wolf;
	iter.x = 1;
	iter.y = p.size;
	coord.y = 0;
	y1 = (H / 2) - 1;
	while (y1 < H)
	{
		coord.x = 0;
		while (coord.x < W - 1)
		{
			if (coord.x + coord.y * W < W * H && coord.x + coord.y * W < W * H)
			{
				if (iter.x < (t_s32)p.size)
				{
					img[coord.x + coord.y * W] = p.palete[iter.x];
					img[coord.x + y1 * W] = p.palete[iter.y];
				}
				else
				{
					img[coord.x + coord.y * W] = 0;
					img[coord.x + y1 * W] = 0;
				}
			}
			coord.x++;
		}
		if (coord.y % 20 == 0)
		{
			iter.x++;
			iter.y--;
		}
		coord.y++;
		y1++;
	}
	//printf("iter.x= %d, %d\n", i, wolf->view);
}

// TODO(viccarau): In order to create the pallete, we can calculate the H * 2,
// then the middle point is where the pallete starts to draw
