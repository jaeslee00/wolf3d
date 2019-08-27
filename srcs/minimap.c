/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 03:17:52 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/27 04:21:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_square(unsigned int *img, int color, t_2d_p minimap, int size)
{
	int	x;
	int	y;

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

void draw_minimap(t_wolf *wolf)
{
	t_2d_p		minimap;
	int			size;
	int			lines;

	size = W / 10 / wolf->obj.len;
	lines = wolf->obj.size / wolf->obj.len;
	minimap.x = 0;
	while (minimap.x < lines)
	{
		minimap.y = 0;
		while (minimap.y < wolf->obj.len)
		{
			if (wolf->map[minimap.x][minimap.y] == 1)
				draw_square(wolf->img, 0xFFFFFF, minimap, size);
			else if (wolf->map[minimap.x][minimap.y] == 3 || wolf->map[minimap.x][minimap.y] == 5)
				draw_square(wolf->img, 0xFF0000, minimap, size);
			minimap.y++;
		}
		minimap.x++;
	}
	minimap.x = (int)wolf->player.pos.x;
	minimap.y = (int)wolf->player.pos.y;
	draw_square(wolf->img, 0x00FF00, minimap, size);
}
