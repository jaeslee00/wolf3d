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


void	init_precalc(t_precalc *calc)
{
	int i;

	i = 0;
	while (i < 360)
	{
		calc->sins[i] = my_sin(degree_radian(i));
		calc->asins[i] = my_asin(degree_radian(i));
		calc->cosins[i] = my_cos(degree_radian(i));
		calc->acosins[i] = my_acos(degree_radian(i));
		calc->tan[i] = my_tan(degree_radian(i));
		calc->atan[i] = my_atan(degree_radian(i));
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
