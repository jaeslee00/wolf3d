/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:38:57 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 18:45:20 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_2d_p	init_2d(t_s32 x, t_s32 y)
{
	t_2d_p	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

void	draw_sprite(t_wolf *wolf, t_2d_p start, t_texture tex, t_u32 size)
{
	t_2d_p xy;
	t_2d_p sprite;

	xy.y = start.y;
	sprite.y = 2;
	while (sprite.y < tex.height)
	{
		sprite.x = 2;
		xy.x = start.x;
		while (sprite.x < tex.width)
		{
			if (tex.data[sprite.x + sprite.y * tex.width] != 0xFFFFFF)
				wolf->img[xy.x + xy.y * W] =
				tex.data[sprite.x + sprite.y * tex.width];
			xy.x++;
			if (xy.x % size == 0)
				sprite.x++;
		}
		xy.y++;
		if (xy.y % size == 0)
			sprite.y++;
	}
}
