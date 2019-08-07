/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:57:38 by viccarau          #+#    #+#             */

/*   Updated: 2019/07/30 15:57:38 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
TILE_SIZE = 64;
WALL_HEIGHT = 64;
PROJECTIONPLANEWIDTH = 1280;
PROJECTIONPLANEHEIGHT = 720;
ANGLE80 = W;
ANGLE40 = (W / 2);
ANGLE20 = (W / 4);
ANGLE60 = (W / 4) * 3;
ANGLE30 = ((W / 4) * 3) / 2;
ANGLE90 = (((W / 4) * 3) / 2) * 3;
ANGLE180 = (((W / 4) * 3) / 2) * 6;
ANGLE270 = (((W / 4) * 3) / 2) * 9;
ANGLE360 = (W / 4) * 18;
ANGLE0 = 0;
ANGLE5 = W / 16;
ANGLE10 = W / 8;
*/

void	init_precalc(t_steps *steps)
{
	int		i;

	i = 0;
	while (i <= (W / 4) * 18)
	{
		if (i >= (((W / 4) * 3) / 2) * 3 &&
			i < (((W / 4) * 3) / 2) * 9)
		{
			steps->x_step[i] = (float)(64 /
				(my_tan(degree_radian(i) + 0.0001)));
			if (steps->x_step[i] > 0)
				steps->x_step[i] = -steps->x_step[i];
		}
		else
		{
			steps->x_step[i] = (float)(64 /
				(my_tan(degree_radian(i) + 0.0001)));
			if (steps->x_step[i] < 0)
				steps->x_step[i] = -steps->x_step[i];
		}
		if (i >= 0 && i < (((W / 4) * 3) / 2) * 6)
		{
			steps->y_step[i] = (float)(64 *
				(my_tan(degree_radian(i) + 0.0001)));
			if (steps->y_step[i] < 0)
				steps->y_step[i] = -steps->y_step[i];
		}
		else
		{
			steps->y_step[i] = (float)(64 *
									   (my_tan(degree_radian(i) + 0.0001)));
			if (steps->y_step[i] > 0)
				steps->y_step[i] = -steps->y_step[i];
		}
	i++;
}
	i = -480;
	while (i <= 480)
	{
		steps->correction[i + 480] = (float)(1.0f / my_cos(degree_radian(i)));
		i++;
	}
}

void	calculate_distance(t_player *p, t_2d_p *a)
{
p->ray.y = (p->position.y >> 8) * (64) - 1;
p->ray.x = (p->position.x) + (p->position.y - p->ray.y) / my_tan(FOV);
a->y = -64;
a->x = 64 / my_tan(FOV);
}

void	ft_raycast(t_wolf *wolf, t_player *player)
{
t_2d_p a;
t_2d_p *ray;
int x;
int y;
int hit;
int **map;

map = int_to_tab(wolf->obj);
calculate_distance(player, &a);
ray = &player->ray;
hit = 0;
while (!hit)
{
	x = (ray->x + a.x);
	y = (ray->y + a.y);
	if (map[ray->y >> 8][ray->x >> 8] == 64)
		hit = 1;
}
printf("x = %d %d\n", x, y);
}
