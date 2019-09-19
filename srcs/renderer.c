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

void		back(t_wolf *wolf, t_u32 *img, t_palette *cel)
{
	t_u32	x;
	t_u32	y;
	t_u32	y1;
	t_u32	i;
	t_u32	j;

	(void)wolf;
	i = 1;
	j = 29;
	y = 0;
	y1 = (H / 2) - 1;
	while (y1 < H)
	{
		x = 0;
		while (x < W - 1)
		{
			if (x + y * W < W * H && x + y * W < W * H)
			{
				if (i < cel->size)
				{
					img[x + y * W] = cel->palete[i];
					img[x + y1 * W] = cel->palete[j];
				}
				else
				{
					img[x + y * W] = 0;
					img[x + y1 * W] = 0;
				}
			}
			x++;
		}
		if (y % 20 == 0)
		{
			i++;
			j--;
		}
		y++;
		y1++;
	}
	//printf("i = %d, %d\n", i, wolf->view);
}

// TODO(viccarau): In order to create the pallete, we can calculate the H * 2,
// then the middle point is where the pallete starts to draw
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
