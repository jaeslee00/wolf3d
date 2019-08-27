/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 04:27:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/27 06:23:30 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_square(uint32 *img, t_2d_p minimap, sint32 size, sint32 color)
{
	sint32	x;
	sint32	y;

	x = size * 2 + size * minimap.x;
	while (x < size * 2 + (size * (minimap.x + 1)))
	{
		y = size * 2 + size * minimap.y;
		while (y < size * 2 + (size * (minimap.y + 1)))
		{

			img[x * W + y] = color;
			y++;
		}
		x++;
	}
}

void	minimap(t_wolf *wolf)
{
	t_2d_p			minimap;
	sint32			square_size;
	sint32			map_width;
	sint32			map_height;
	square_size = W / 10 / wolf->obj.len;
	map_height = wolf->obj.size / wolf->obj.len;
	map_width = wolf->obj.len;
	minimap.x = 0;
	while (minimap.x < map_height)
	{
		minimap.y = 0;
		while (minimap.y < map_width)
		{
			if (wolf->map[minimap.x][minimap.y] == 1)
				draw_square(wolf->img, minimap, square_size, 0xFFFFFF);
			else if (wolf->map[minimap.x][minimap.y] == 3
				|| wolf->map[minimap.x][minimap.y] == 5)
				draw_square(wolf->img, minimap, square_size, 0xFF0000);
			minimap.y++;
		}
		minimap.x++;
	}
	minimap.x = (sint32)wolf->player.pos.x;
	minimap.y = (sint32)wolf->player.pos.y;
	draw_square(wolf->img, minimap, square_size, 0x00FF00);
}
