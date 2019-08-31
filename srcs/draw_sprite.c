/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:38:57 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/31 13:57:54 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_2d_p init_2d(sint32 x, sint32 y)
{
	t_2d_p coord;

	coord.x = x;
	coord.y = y;
return (coord);
}

void	draw_sprite(t_wolf *wolf, t_2d_p start, t_texture tex)
{
	t_2d_p xy;
	t_2d_p sprite;
	t_2d_p size;

	xy.y = start.y;
	sprite.y = 2;
	while (sprite.y < tex.height)
	{
		size.y = 0;
		sprite.x = 2;
		xy.x = start.x;
		while (sprite.x < tex.width)
		{
			size.x = 0;
			if (tex.data[sprite.x + sprite.y * tex.width] != 0xFFFFFF)
				wolf->img[xy.x + xy.y * W] = tex.data[sprite.x + sprite.y * tex.width];
				xy.x++;
			sprite.x++;
				}
			xy.y++;
		sprite.y++;
		}
}