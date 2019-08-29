/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 04:27:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/29 03:39:35 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// minimap[x + y * map_width].x = x * zoom + W / 2 - zoom * (map_width / 2) - zoom * (wolf->player.pos.y * 2 - map_width) / 2.0 + zoom;
// minimap[x + y * map_width].y = y * zoom + H / 2 - zoom * (map_height / 2) - zoom * (wolf->player.pos.x * 2 - map_height) / 2.0 + zoom;

#include "wolf3d.h"

void	draw_player(uint32 *img)
{
	sint32	size;
	sint32	x;
	sint32	y;
	sint32	i;
	sint32	j;

	y = 0;
	i = W / 2 - 4;
	j = H / 2 - 4;
	size = 9;
	while (y < size)
	{
		x = 0;
		i = W / 2 - 4;
		while (x < size)
		{
			img[i + j * W] = 0x00FF00;
			x++;
			i++;
		}
		j++;
		y++;
	}
}
int gflag;
void	draw_line_x(t_minimap p1, t_minimap p2, uint32 *img)
{
	t_2d_p d;
	t_2d_p curr;
	int yi;
	int diff;
	if (!gflag)
	{	printf("%d %d\n", p1.type, p2.type);
		gflag++;
	}
	curr.y = p1.y;
	curr.x = p1.x;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	yi = d.y < 0 ? -1 : 1;
	d.y = abs(d.y);
	diff = 2 * d.y - d.x;
	while (curr.x < p2.x)
	{
		if (curr.x + curr.y * W < H * W && curr.x > 0 && curr.y > 0)
			img[curr.x + curr.y * W] = (p1.type == 1 && p2.type == 1) ? 0xFFFFFF : 0;
		if (diff > 0)
		{
			curr.y += yi;
			diff = diff - 2 * d.x;
		}
		diff = diff + 2 * d.y;
		curr.x++;
	}
}

void draw_line_y(t_minimap p1, t_minimap p2, uint32 *img)
{
	t_2d_p d;
	t_2d_p curr;
	int xi;
	int diff;

	curr.x = p1.x;
	curr.y = p1.y;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	xi = d.x < 0 ? -1 : 1;
	d.x = abs(d.x);
	diff = 2 * d.x - d.y;
	while (curr.y < p2.y)
	{
		if (curr.x + curr.y * W < H * W && curr.x > 0 && curr.y > 0)
			img[curr.x + curr.y * W] = (p1.type == 1 && p2.type == 1) ? 0xFFFFFF : 0;
		if (diff > 0)
		{
			curr.x += xi;
			diff = diff - 2 * d.y;
		}
		diff = diff + 2 * d.x;
		curr.y++;
	}
}

void draw_line(t_minimap p1, t_minimap p2, uint32 *img)
{
	if (abs(p1.y - p2.y) < abs(p1.x - p2.x))
	{
		if (p1.x > p2.x)
			draw_line_x(p2, p1, img);
		else
			draw_line_x(p1, p2, img);
	}
	else
	{
		if (p1.y > p2.y)
			draw_line_y(p2, p1, img);
		else
			draw_line_y(p1, p2, img);
	}
}
//TODO (jae) : gotta clean this shit up tomorrow... Don't be triggered please.. T-T
void	minimap(t_wolf *wolf)
{
	t_2d_p			coord;
	sint32			square_size;
	sint32			map_width;
	sint32			map_height;
	sint32			minimap_width;
	sint32			minimap_height;
	sint32			zoom = 50;

	map_height = wolf->obj.size / wolf->obj.len;
	map_width = wolf->obj.len;
	minimap_width = map_width + 1;
	minimap_height = map_height + 1;
	t_minimap *minimap = (t_minimap *)ft_memalloc((minimap_height) * (minimap_width) * sizeof(t_minimap));
	int x = 0;
	int y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			//TODO (jae) : figure out exact ways to transform map... and i'm going to change everything to maxtrix later!
			minimap[x + y * minimap_width].x = x * zoom + W / 2 - zoom * minimap_width / 2;
			minimap[x + y * minimap_width].y = y * zoom + H / 2 - zoom * minimap_height / 2;

			minimap[(x + 1) + y * minimap_width].x = (x + 1) * zoom + W / 2 - zoom * minimap_width / 2;
			minimap[(x + 1) + y * minimap_width].y = y * zoom + H / 2 - zoom * minimap_height / 2;

			minimap[x + (y + 1) * minimap_width].x = x * zoom + W / 2 - zoom * minimap_width / 2;
			minimap[x + (y + 1) * minimap_width].y = (y + 1) * zoom + H / 2 - zoom * minimap_height / 2;

			minimap[(x + 1) + (y + 1) * minimap_width].x = (x + 1) * zoom + W / 2 - zoom * minimap_width / 2;
			minimap[(x + 1) + (y + 1) * minimap_width].y = (y + 1) * zoom + H / 2 - zoom * minimap_height / 2;

			if (wolf->obj.nb[x + y * map_width] == 1)
			{
				minimap[x + y * minimap_width].type = 1;
				minimap[(x + 1) + y * minimap_width].type = 1;
				minimap[x + (y + 1) * minimap_width].type = 1;
				minimap[(x + 1) + (y + 1) * minimap_width].type = 1;
			}
			else if (wolf->obj.nb[x + y * map_width] == 0)
			{
				if (minimap[x + y * minimap_width].type != 1)
					minimap[x + y * minimap_width].type = 0;
				if (minimap[x + 1 + y * minimap_width].type != 1)
					minimap[x + 1 + y * minimap_width].type = 0;
				if (minimap[x + (y + 1) * minimap_width].type != 1)
					minimap[x + (y + 1) * minimap_width].type = 0;
				if (minimap[x + 1 + (y + 1) * minimap_width].type != 1)
					minimap[x + 1 + (y + 1) * minimap_width].type = 0;
			}
			x++;
		}
		y++;
	}
	y = 0;
	//printf("%d %d\n", minimap[0].type, minimap[1].type);
	while (y < minimap_height)
	{
		x = 0;
		while (x < minimap_width)
		{
			if (x < minimap_width - 1)
				draw_line(minimap[x + y * minimap_width],
					minimap[(x + 1) + y * minimap_width], wolf->img);
			if (y < minimap_height - 1)
				draw_line(minimap[x + y * minimap_width],
					minimap[x + (y + 1) * minimap_width], wolf->img);
			x++;
		}
		y++;
	}
	draw_player(wolf->img);
}
