/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perp_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:50:11 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/28 15:02:44 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

f32		perp_distance_ew(t_raycaster *ray, t_player player)
{
	return ((ray->map.x - player.pos.x + (1 - ray->step.x) / 2) / player.ray.x);
}

f32		perp_distance_sn(t_raycaster *ray, t_player player)
{
	return ((ray->map.y - player.pos.y + (1 - ray->step.y) / 2) / player.ray.y);
}

f32		perp_distance_ew_door(t_raycaster *ray, t_player player)
{
	return ((ray->map.y + 0.5f - player.pos.y) / player.ray.y);
}

f32		perp_distance_sn_door(t_raycaster *ray, t_player player)
{
	return ((ray->map.x + 0.5f - player.pos.x) / player.ray.x);
}

funct	*perp_dist(t_wolf *wolf)
{
	funct	*dist;

	is_alloc(dist = ft_mem(&wolf->mem, sizeof(funct) * 4), wolf, -1);
	dist[0] = perp_distance_ew;
		dist[1] = perp_distance_sn;
		dist[2] = perp_distance_ew_door;
		dist[3] = perp_distance_sn_door;
	return (dist);
}
