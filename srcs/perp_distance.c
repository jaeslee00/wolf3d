/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perp_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:50:11 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/28 12:27:09 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// NOTE (victor): Never use global variables, even if the subject allows it
//               The only time to use global variables is if you want to test
//               something fast, or if something really needs to be global.

f32	perp_distance_ew(t_raycaster *ray, t_player player)
{
	return ((ray->map.x - player.pos.x + (1 - ray->step.x) / 2) / player.ray.x);
}

f32	perp_distance_sn(t_raycaster *ray, t_player player)
{
	return ((ray->map.y - player.pos.y + (1 - ray->step.y) / 2) / player.ray.y);
}

f32	perp_distance_ew_door(t_raycaster *ray, t_player player)
{
	return ((ray->map.y + 0.5f - player.pos.y) / player.ray.y);
}

f32	perp_distance_sn_door(t_raycaster *ray, t_player player)
{
	return ((ray->map.x + 0.5f - player.pos.x) / player.ray.x);
}

perp_distance *perp_dist()
{
	perp_distance *dist;

	dist = ft_memalloc(sizeof(dist) * 4);
	dist[0] = perp_distance_ew;
		dist[1] = perp_distance_sn;
		dist[2] = perp_distance_ew_door;
		dist[3] = perp_distance_sn_door;
	return (dist);
}
