/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:47:24 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/23 18:52:49 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*t_m4x4	final_projection(t_wolf *wolf)
{
	wolf->proj_matrix = mx_mul(mx_mul(ortho_proj(W / H, 1, 1000).forward,
	cam_obj_matrix(*wolf)),
						mx_mul(scaling(wolf->scale), z_scaling(wolf->zscale)));
	wolf->proj_matrix = translate(wolf->proj_matrix, find_center(*wolf));
	return (wolf->proj_matrix);
}

void	initialize_cam(t_wolf *wolf)
{
	wolf->flags = 0;
	wolf->zscale = 0.1f;
	wolf->loc.camx = point(1, 0, 0, 0).xyz.xyz;
	wolf->loc.camy = point(0, 1, 0, 0).xyz.xyz;
	wolf->loc.camz = point(0, 0, 1, 0).xyz.xyz;
	wolf->loc.camp = point(0, 0, 0, 0).xyz.xyz;
	wolf->cam = get_standard_camera();
	wolf->proj_matrix = final_projection(wolf);
	}

t_cam	get_standard_camera(void)
{
	t_cam	res;

	res.pitch = 0;
	res.orbit = 0.03f;
	res.dolly = 20.0f;
	res.focal_length = 3.0f;
	res.near_clip = 0.2f;
	res.far_clip = 1000.0f;
	res.offset = point(0, 0, 0, 0).xyz.xyz;
	res.shift = point(0, 0, -1.0f, 0).xyz.xyz;
	return (res);
}
*/