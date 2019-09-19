/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:57:38 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/07 22:44:10 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	raycast_collision(t_s8 **map, t_raycaster *ray, int *hit)
{
	if (map[ray->map.y][ray->map.x] == 1)
		*hit = 1;
	else if (map[ray->map.y][ray->map.x] == 3)
	{
		if (ray->side_dist.x < ray->side_dist.y + 0.5f)
		{
			*hit = 1;
			ray->side = 3;
		}
	}
	else if (map[ray->map.y][ray->map.x] == 5)
	{
		if (ray->side_dist.y < ray->side_dist.x + 0.5f)
		{
			*hit = 1;
			ray->side = 2;
		}
	}
}

t_s32	dda_raycast(t_wolf *wf, t_raycaster *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		raycast_collision(wf->map, ray, &hit);
	}
	return (ray->side);
}

void	dda_init(t_raycaster *ray, t_player *p)
{
	ray->delta_dist.x = fabs(1.0f / p->ray.x);
	ray->delta_dist.y = fabs(1.0f / p->ray.y);
	ray->map.x = (t_s32)p->pos.x;
	ray->map.y = (t_s32)p->pos.y;
	if (p->ray.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (p->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (1.0f + ray->map.x - p->pos.x) * ray->delta_dist.x;
	}
	if (p->ray.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (p->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (1.0f + ray->map.y - p->pos.y) * ray->delta_dist.y;
	}
}

void	raycast(t_wolf *wf)
{
	t_raycaster	ray;
	t_f32			line_height;
	t_s32		x;
	t_f32			scale;
	t_f32			cam_scale;

	scale = 2.0f / (t_f32)W;
	x = 0;
	while (x < W)
	{
		cam_scale = (x * scale - 1.0f);
		wf->player->ray.y = wf->player->direction.y +
			wf->player->plane.y * cam_scale;
		wf->player->ray.x = wf->player->direction.x +
			wf->player->plane.x * cam_scale;
		dda_init(&ray, wf->player);
		dda_raycast(wf, &ray);
		ray.perp_dist = wf->dist[ray.side](&ray, wf->player);
		wf->perp_dist[x] = ray.perp_dist;
		line_height = (t_s32)((t_f32)H / ray.perp_dist);
		if (line_height > 1)
			draw_wall(wf, line_height, x, &ray);
		x++;
	}
}
