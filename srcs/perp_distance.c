/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perp_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:50:11 by jaelee            #+#    #+#             */
/*   Updated: 2019/10/07 20:20:21 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_f32		perp_distance_ew(t_raycaster *ray, t_player *player)
{
	return ((ray->map.x - player->pos.x +
			(1 - ray->step.x) / 2) / player->ray.x);
}

t_f32		perp_distance_sn(t_raycaster *ray, t_player *player)
{
	return ((ray->map.y - player->pos.y +
			(1 - ray->step.y) / 2) / player->ray.y);
}

t_f32		perp_distance_sn_door(t_raycaster *ray, t_player *player)
{
	return ((ray->map.y + 0.5f - player->pos.y) /
			player->ray.y);
}

t_f32		perp_distance_ew_door(t_raycaster *ray, t_player *player)
{
	return ((ray->map.x + 0.5f - player->pos.x) /
			player->ray.x);
}

t_funct		*perp_dist(t_wolf *wolf)
{
	t_funct	*dist;

	is_alloc(dist = ft_mem(&wolf->mem, sizeof(t_funct) * 4), wolf, -1);
	dist[0] = perp_distance_ew;
	dist[1] = perp_distance_sn;
	dist[2] = perp_distance_sn_door;
	dist[3] = perp_distance_ew_door;
	return (dist);
}
