/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:51:11 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/15 16:15:54 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "camera.h"

t_m4x4_inv	pers_proj(float wheight, float focal, float n, float f)
{
	t_m4x4_inv	result;

	result.forward = identity();
	result.inverse = identity();
	result.forward.e[0][0] = 1.0f * focal;
	result.forward.e[1][1] = wheight * focal;
	result.forward.e[2][2] = (n + f) / (n - f);
	result.forward.e[2][3] = (2 * f * n) / (n - f);
	result.forward.e[3][2] = 1;
	result.inverse.e[0][0] = 1 / (1.0f * focal);
	result.inverse.e[1][1] = 1 / wheight;
	result.inverse.e[2][3] = -1;
	result.inverse.e[3][2] = 1 / ((2 * f * n) / (n - f));
	result.inverse.e[3][3] = ((n + f) / (n - f)) / ((2 * f * n) / (n - f));
	return (result);
}

t_m4x4_inv	ortho_proj(float wheight, float n, float far)
{
	t_m4x4_inv	result;

	result.forward = identity();
	result.inverse = identity();
	result.forward.e[0][0] = 1.0f;
	result.forward.e[1][1] = wheight;
	result.forward.e[2][2] = 2.0f / (n - far);
	result.forward.e[2][3] = (n + far) / (n - far);
	result.inverse.e[0][0] = 1 / 1.0f;
	result.inverse.e[1][1] = 1 / wheight;
	result.inverse.e[2][2] = 1 / 2.0f / (n - far);
	result.inverse.e[2][3] = -((n + far) / (n - far)) / 2.0f / (n - far);
	return (result);
}

t_m4x4_inv	camera_transform(t_3d x, t_3d y, t_3d z, t_3d p)
{
	t_m4x4_inv	result;
	t_m4x4		a;
	t_3d		ap;

	a = rows3x3(x, y, z);
	ap = transform(a, vector4(p, 1.0f)).xyz.xyz;
	a = translate(a, ap);
	result.forward = a;
	result.inverse = identity();
	return (result);
}

t_m4x4		cam_obj_matrix(t_fdf fdf)
{
	t_3d	v3;
	t_m4x4	res;

	v3.xyz.x = fdf.cam.offset.xyz.x;
	v3.xyz.y = fdf.cam.offset.xyz.y;
	v3.xyz.z = fdf.cam.dolly;
	if (fdf.flags & ISO_PROJ)
	{
		res = mx_mul(
			translation(fdf.cam.offset),
		mx_mul(z_rot(0), mx_mul(x_rot(-0.6154f),
		mx_mul(y_rot(-0.785f), mx_mul(translation(v3), x_rot(1.5707f))))));
		return (res);
	}
	res = mx_mul(
		translation(fdf.cam.offset),
		mx_mul(z_rot(fdf.cam.zrot), mx_mul(x_rot(fdf.cam.pitch),
			mx_mul(y_rot(fdf.cam.orbit), mx_mul(translation(v3), x_rot(0))))));
	return (res);
}
