/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 04:27:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/30 09:17:13 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		{
			if (p1.h_color_head == p2.h_color_tail && p1.h_color_head > 0)
			{
				img[curr.x + curr.y * W] =  0xFFFFFF;
			}
			else if (p1.h_color_head == p2.h_color_tail && p1.h_color_head < 0)
			{
				img[curr.x + curr.y * W] = 0xFF0000;
			}
			else
			{
				img[curr.x + curr.y * W] = 0;
			}
		}
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
		{
			if (p1.v_color_head == p2.v_color_tail && p1.v_color_head > 0)
			{
				img[curr.x + curr.y * W] = 0xFFFFFF;
			}
			else if (p1.v_color_head == p2.v_color_tail && p1.v_color_head < 0)
			{
				img[curr.x + curr.y * W] = 0xFF0000;
			}
			else
			{
				img[curr.x + curr.y * W] = 0;
			}
		}
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
	sint32			map_width;
	sint32			map_height;
	sint32			minimap_width;
	sint32			minimap_height;
	sint32			zoom = 20;
	sint32			x_key = 0;
	sint32			y_key = 0;

	map_height = wolf->obj.size / wolf->obj.len;
	map_width = wolf->obj.len;
	minimap_width = map_width + 1;
	minimap_height = map_height + 1;
	int x = 0;
	int y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			//TODO (jae) : figure out exact ways to transform map... and i'm going to change everything to maxtrix later!
			wolf->player.m[x + y * minimap_width].x = x * zoom + W / 2 - zoom * minimap_width / 2 - zoom * (wolf->player.pos.y * 2.0 - minimap_width) / 2.0;
			wolf->player.m[x + y * minimap_width].y = y * zoom + H / 2 - zoom * minimap_height / 2 - zoom * (wolf->player.pos.x * 2.0 - minimap_height) / 2.0 ;

			wolf->player.m[(x + 1) + y * minimap_width].x = (x + 1) * zoom + W / 2 - zoom * minimap_width / 2 - zoom * (wolf->player.pos.y * 2 - minimap_width) / 2.0 ;
			wolf->player.m[(x + 1) + y * minimap_width].y = y * zoom + H / 2 - zoom * minimap_height / 2 - zoom * (wolf->player.pos.x * 2 - minimap_height) / 2.0;

			wolf->player.m[x + (y + 1) * minimap_width].x = x * zoom + W / 2 - zoom * minimap_width / 2 - zoom * (wolf->player.pos.y * 2 - minimap_width) / 2.0 ;
			wolf->player.m[x + (y + 1) * minimap_width].y = (y + 1) * zoom + H / 2 - zoom * minimap_height / 2 - zoom * (wolf->player.pos.x * 2 - minimap_height) / 2.0 ;

			wolf->player.m[(x + 1) + (y + 1) * minimap_width].x = (x + 1) * zoom + W / 2 - zoom * minimap_width / 2 - zoom * (wolf->player.pos.y * 2 - minimap_width) / 2.0 ;
			wolf->player.m[(x + 1) + (y + 1) * minimap_width].y = (y + 1) * zoom + H / 2 - zoom * minimap_height / 2 - zoom * (wolf->player.pos.x * 2 - minimap_height) / 2.0 ;

			if (x > 0 && y > 0)
			{
				if (y == 1)
					wolf->player.m[x + y * minimap_width].v_color_tail = INT_MAX;
				if (x == 1)
					wolf->player.m[x + y * minimap_width].h_color_tail = INT_MAX;
				if (!(wolf->obj.nb[x + y * map_width] == 0 && wolf->obj.nb[x - 1 + y * map_width] == 0))
				{
					if (wolf->obj.nb[x + y * map_width] > 2 || wolf->obj.nb[x - 1 + y * map_width] > 2)
					{
						wolf->player.m[x + y * minimap_width].v_color_head = -1;
						wolf->player.m[x + (y + 1) * minimap_width].v_color_tail = -1;
					}
					else
					{
						y_key++;
						wolf->player.m[x + y * minimap_width].v_color_head = y_key;
						wolf->player.m[x + (y + 1) * minimap_width].v_color_tail = y_key;
					}
				}
				if (!(wolf->obj.nb[x + y * map_width] == 0 && wolf->obj.nb[x + (y - 1) * map_width] == 0))
				{
					if (wolf->obj.nb[x + y * map_width] > 2 || wolf->obj.nb[x + (y - 1 ) * map_width] > 2)
					{
						wolf->player.m[x + y * minimap_width].h_color_head = -1;
						wolf->player.m[x + 1 + y * minimap_width].h_color_tail = -1;
					}
					else
					{
						x_key++;
						wolf->player.m[x + y * minimap_width].h_color_head = x_key;
						wolf->player.m[x + 1 + y * minimap_width].h_color_tail = x_key;
					}
				}
			}
			else
			{
				wolf->player.m[x + y * minimap_width].h_color_head = INT_MAX;
				wolf->player.m[x + y * minimap_width].h_color_tail = INT_MAX;
				wolf->player.m[x + y * minimap_width].v_color_head = INT_MAX;
				wolf->player.m[x + y * minimap_width].v_color_tail = INT_MAX;
			}
			x++;
		}
		y++;
	}
	y = 0;
	while (y < minimap_height)
	{
		wolf->player.m[minimap_width - 1 + y * minimap_width].v_color_head = INT_MAX;
		wolf->player.m[minimap_width - 1 + y * minimap_width].v_color_tail = INT_MAX;
		y++;
	}
	x = 0;
	while (x < minimap_width)
	{
		wolf->player.m[x + (minimap_height -1) * minimap_width].h_color_head = INT_MAX;
		wolf->player.m[x + (minimap_height - 1) * minimap_width].h_color_tail = INT_MAX;
		x++;
	}
	wolf->player.m[minimap_width - 2].h_color_head = INT_MAX;
	wolf->player.m[minimap_width - 1].h_color_tail = INT_MAX;
	wolf->player.m[(minimap_width - 2) * minimap_width].v_color_head = INT_MAX;
	wolf->player.m[(minimap_width - 1)*minimap_width].v_color_tail = INT_MAX;
	y = 0;
	while (y < minimap_height)
	{
		x = 0;
		while (x < minimap_width)
		{
			if (x < minimap_width - 1)
				draw_line(wolf->player.m[x + y * minimap_width],
					wolf->player.m[(x + 1) + y * minimap_width], wolf->img);
			if (y < minimap_height - 1)
				draw_line(wolf->player.m[x + y * minimap_width],
					wolf->player.m[x + (y + 1) * minimap_width], wolf->img);
			x++;
		}
		y++;
	}
	draw_player(wolf->img);
}
