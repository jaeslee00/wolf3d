/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perp_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 22:50:11 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/28 00:33:04 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//NOTE (jae) : the subject says we cannot use global variables.. But i'm not sure if array of func_ptrs is a global variable lul..

f32		(*g_perp_dist_tab[4])(t_raycaster*, t_player) = {
	perp_distance_ew,
	perp_distance_sn,
	perp_distance_ew_door,
	perp_distance_sn_door
};

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
