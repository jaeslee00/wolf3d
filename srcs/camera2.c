/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:47:24 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/15 16:17:58 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_m4x4	final_projection(t_fdf *fdf)
{
	fdf->proj_matrix = mx_mul(mx_mul(ortho_proj(W / H, 1, 1000).forward,
	cam_obj_matrix(*fdf)),
						mx_mul(scaling(fdf->scale), z_scaling(fdf->zscale)));
	fdf->proj_matrix = translate(fdf->proj_matrix, find_center(*fdf));
	return (fdf->proj_matrix);
}

void	initialize_cam(t_fdf *fdf)
{
	fdf->flags = 0;
	fdf->zscale = 0.1f;
	fdf->loc.camx = point(1, 0, 0, 0).xyz.xyz;
	fdf->loc.camy = point(0, 1, 0, 0).xyz.xyz;
	fdf->loc.camz = point(0, 0, 1, 0).xyz.xyz;
	fdf->loc.camp = point(0, 0, 0, 0).xyz.xyz;
	fdf->cam = get_standard_camera();
	fdf->proj_matrix = final_projection(fdf);
	fdf->offset = point(0, 0, 0, 0).xyz.xyz;
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
