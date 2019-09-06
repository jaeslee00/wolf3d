/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 04:27:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/09/06 03:09:44 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

sint32	get_color_horiz(t_minimap *p1, t_minimap *p2)
{
	if (p1->h_color_head == p2->h_color_tail && p1->h_color_head > 0)
		return (0xFFFFFF);
	else if (p1->h_color_head == p2->h_color_tail && p1->h_color_head < 0)
		return (0xFF0000);
	else
		return (0x00);
}

sint32	get_color_vertical(t_minimap *p1, t_minimap *p2)
{
	if (p1->v_color_head == p2->v_color_tail && p1->v_color_head > 0)
		return (0xFFFFFF);
	else if (p1->v_color_head == p2->v_color_tail && p1->v_color_head < 0)
		return (0xFF0000);
	else
		return (0x00);
}

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
			img[curr.x + curr.y * W] =  get_color_horiz(&p1, &p2);
		if (diff > 0)
		{
			curr.y += yi;
			diff = diff - 2 * d.x;
		}
		diff = diff + 2 * d.y;
		curr.x++;
	}
}

void	draw_line_y(t_minimap p1, t_minimap p2, uint32 *img)
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
			img[curr.x + curr.y * W] = get_color_vertical(&p1, &p2);
		if (diff > 0)
		{
			curr.x += xi;
			diff = diff - 2 * d.y;
		}
		diff = diff + 2 * d.x;
		curr.y++;
	}
}

void	draw_line(t_minimap p1, t_minimap p2, uint32 *img)
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

void	minimap_render(t_wolf *wolf, sint32 minimap_width, sint32 minimap_height)
{
	sint32	x;
	sint32	y;

	y = 0;
	while (y < minimap_height)
	{
		x = 0;
		while (x < minimap_width)
		{
			if (x < minimap_width - 1)
				draw_line(wolf->player->m[x + y * minimap_width],
					wolf->player->m[(x + 1) + y * minimap_width], wolf->img);
			if (y < minimap_height - 1)
				draw_line(wolf->player->m[x + y * minimap_width],
					wolf->player->m[x + (y + 1) * minimap_width], wolf->img);
			x++;
		}
		y++;
	}
}

void	minimap_set_edge_color(t_minimap *m, sint32 minimap_width, sint32 minimap_height)
{
	sint32	x;
	sint32	y;

	y = 0;
	while (y < minimap_height)
	{
		m[minimap_width - 1 + y * minimap_width].v_color_head = INT_MAX;
		m[minimap_width - 1 + y * minimap_width].v_color_tail = INT_MAX;
		y++;
	}
	x = 0;
	while (x < minimap_width)
	{
		m[x + (minimap_height -1) * minimap_width].h_color_head = INT_MAX;
		m[x + (minimap_height - 1) * minimap_width].h_color_tail = INT_MAX;
		x++;
	}
	m[minimap_width - 2].h_color_head = INT_MAX;
	m[minimap_width - 1].h_color_tail = INT_MAX;
	m[(minimap_height - 2) * minimap_width].v_color_head = INT_MAX;
	m[(minimap_height - 1) * minimap_width].v_color_tail = INT_MAX;
}

void	minimap_obj_color_vertical(t_wolf *wolf, sint32 x, sint32 y, sint32 *y_key)
{
	sint32	minimap_width;

	minimap_width = wolf->player->minimap_width;
	if (wolf->obj.nb[x + y * wolf->map_width] == 3
		|| wolf->obj.nb[x - 1 + y * wolf->map_width] == 3
		|| wolf->obj.nb[x + y * wolf->map_width] == 5
		|| wolf->obj.nb[x - 1 + y * wolf->map_width] == 5)
	{
		wolf->player->m[x + y * minimap_width].v_color_head = -1;
		wolf->player->m[x + (y + 1) * minimap_width].v_color_tail = -1;
	}
	else
	{
		(*y_key)++;
		wolf->player->m[x + y * minimap_width].v_color_head = *y_key;
		wolf->player->m[x + (y + 1) * minimap_width].v_color_tail = *y_key;
	}
}

void	minimap_obj_color_horiz(t_wolf *wolf, sint32 x, sint32 y, sint32 *x_key)
{
	sint32	minimap_width;

	minimap_width = wolf->player->minimap_width;
	if (wolf->obj.nb[x + y * wolf->map_width] == 3
		|| wolf->obj.nb[x + (y - 1) * wolf->map_width] == 3
		|| wolf->obj.nb[x + y * wolf->map_width] == 5
		|| wolf->obj.nb[x + (y - 1) * wolf->map_width] == 5)
	{
		wolf->player->m[x + y * minimap_width].h_color_head = -1;
		wolf->player->m[x + 1 + y * minimap_width].h_color_tail = -1;
	}
	else
	{
		(*x_key)++;
		wolf->player->m[x + y * minimap_width].h_color_head = *x_key;
		wolf->player->m[x + 1 + y * minimap_width].h_color_tail = *x_key;
	}
}

void	minimap_obj_color(t_wolf *wolf, sint32 x, sint32 y)
{
	sint32	x_key;
	sint32	y_key;
	sint32	minimap_width;

	x_key = 0;
	y_key = 0;
	minimap_width = wolf->player->minimap_width;
	if (y == 1)
		wolf->player->m[x + y * minimap_width].v_color_tail = INT_MAX;
	if (x == 1)
		wolf->player->m[x + y * minimap_width].h_color_tail = INT_MAX;
	if (!(wolf->obj.nb[x + y * wolf->map_width] == 0
		&& wolf->obj.nb[x - 1 + y * wolf->map_width] == 0))
		minimap_obj_color_vertical(wolf, x, y, &y_key);
	if (!(wolf->obj.nb[x + y * wolf->map_width] == 0
		&& wolf->obj.nb[x + (y - 1) * wolf->map_width] == 0))
		minimap_obj_color_horiz(wolf, x, y, &x_key);
}

void	uniform_translation(sint32 transform[2], sint32 width, sint32 height, t_wolf *wolf)
{
	sint32	zoom;

	zoom = wolf->player->minimap_zoom;
	transform[0] = W / 2 - zoom * width / 2 -
		(sint32)((f32)zoom * (wolf->player->pos.x * 2.0f - (f32)width) / 2.0f);
	transform[1] = H / 2 - zoom * height / 2 -
		(sint32)((f32)zoom * (wolf->player->pos.y * 2.0f - (f32)height) / 2.0f);
}

void	minimap_transform(t_minimap *m, t_wolf *wolf, sint32 x, sint32 y)
{
	sint32		width;
	sint32		height;
	sint32		zoom;
	sint32		transform[2];

	width = wolf->player->minimap_width;
	height = wolf->player->minimap_height;
	zoom = wolf->player->minimap_zoom;
	uniform_translation(transform, width, height, wolf);
	m[x + y * width].x = x * zoom + transform[0];
	m[x + y * width].y = y * zoom + transform[1];
	m[(x + 1) + y * width].x = (x + 1) * zoom + transform[0];
	m[(x + 1) + y * width].y = y * zoom + transform[1];
	m[x + (y + 1) * width].x = x * zoom + transform[0];
	m[x + (y + 1) * width].y = (y + 1) * zoom + transform[1];
	m[(x + 1) + (y + 1) * width].x = (x + 1) * zoom + transform[0];
	m[(x + 1) + (y + 1) * width].y = (y + 1) * zoom + transform[1];
}

void	minimap(t_wolf *wolf, sint32 minimap_width, sint32 minimap_height)
{
	sint32	x;
	sint32	y;

	y = 0;
	while (y < wolf->map_height)
	{
		x = 0;
		while (x < wolf->map_width)
		{
			minimap_transform(wolf->player->m, wolf, x, y);
			if (x > 0 && y > 0)
				minimap_obj_color(wolf, x, y);
			else
			{
				wolf->player->m[x + y * minimap_width].h_color_head = INT_MAX;
				wolf->player->m[x + y * minimap_width].h_color_tail = INT_MAX;
				wolf->player->m[x + y * minimap_width].v_color_head = INT_MAX;
				wolf->player->m[x + y * minimap_width].v_color_tail = INT_MAX;
			}
			x++;
		}
		y++;
	}
	minimap_set_edge_color(wolf->player->m, minimap_width, minimap_height);
	minimap_render(wolf, minimap_width, minimap_height);
}
