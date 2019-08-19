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
 
int	verLine(int x, int y1, int y2, const int color, unsigned int *img)
{
	int i;
	int y;

	if (y2 < y1)
	{
		y1 += y2;
		y2 = y1 - y2;
		y1 -= y2;
	}
	if (y2 < 0 || y1 >= H  || x < 0 || x >= W)
		return (0);
	if (y1 < 0)
		y1 = 0;
	if (y2 >= W)
		y2 = H - 1;
	y = y1;
	i = 0;
	while (++y < y2)
		img[x + y * W] = color;
	return (1);
}

/*
t_raycaster r;
double perpWallDist;
int hit;
int side;
int x;
*/

void	render(t_wolf *wolf)
{
	int x;
	t_raycaster r;
	x = 0;
 while (x < W)
		{
		r.hit = 0;
		wolf->player.ray.x = wolf->player.direction.x + wolf->player.plane.x * (2 * x / (double)(W) - 1);
		wolf->player.ray.y = wolf->player.direction.y + wolf->player.plane.y * (2 * x / (double)(W) - 1);
		r.delta_dist.x = ft_abs(1 / wolf->player.ray.x);
		 r.delta_dist.y = ft_abs(1 / wolf->player.ray.y);
		  r.map.x = (int)wolf->player.position.x;
		  r.map.y = (int)wolf->player.position.y;
			if (wolf->player.ray.x < 0)
			{
				r.step.x = -1;
				r.side_dist.x = (wolf->player.position.x - r.map.x) * r.delta_dist.x;
			}
			else
			{
				r.step.x = 1;
				r.side_dist.x = (r.map.x + 1.0 - wolf->player.position.x) * r.delta_dist.x;
			}
			if (wolf->player.ray.y < 0)
			{
				r.step.y = -1;
				r.side_dist.y = (wolf->player.position.y - r.map.y) * r.delta_dist.y;
			}
			else
			{
				r.step.y = 1;
				r.side_dist.y = (r.map.y + 1.0 - wolf->player.position.y) * r.delta_dist.y;
			}
			//perform DDA
			while (r.hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (r.side_dist.x < r.side_dist.y)
				{
					r.side_dist.x += r.delta_dist.x;
					r.map.x += r.step.x;
					r.side = 0;
				}
				else
				{
					r.side_dist.y += r.delta_dist.y;
					r.map.y += r.step.y;
					r.side = 1;
				}
			if (wolf->map[r.map.x][r.map.y] == 1 || wolf->map[r.map.x][r.map.y] > 2)
				r.hit = 1;
			}
			if (r.side == 0)
			r.perp_distance = (r.map.x - wolf->player.position.x + (1 - r.step.x) / 2) / wolf->player.ray.x;
			else
			 r.perp_distance = (r.map.y - wolf->player.position.y + (1 - r.step.y) / 2) / wolf->player.ray.y;
		int lineHeight = (int)(H / r.perp_distance);
int drawStart = -lineHeight / 2 + H / 2;
			if (drawStart < 0)
			drawStart = 0;
			int drawEnd = lineHeight / 2 + H / 2;
			if (drawEnd >= H)
			drawEnd = H - 1;
int color;

			if (wolf->map[r.map.x][r.map.y])
			color = 0x440000 * wolf->map[r.map.x][r.map.y];
else
color = 0;
			if (r.side == 1)
		color = color >> 1;
verLine(x, drawStart, drawEnd, color, wolf->img);
		x++;
		}
	}
