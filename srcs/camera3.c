/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:59:26 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/09 12:27:20 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	inner(t_2d a, t_2d b)
{
	float	result;

	result = (a.x * b.x) + (a.y * b.y);
	return (result);
}

t_4d	vector4(t_3d p, float b)
{
	t_4d point;

	point.xyzw.x = p.xyz.x;
	point.xyzw.y = p.xyz.y;
	point.xyzw.z = p.xyz.z;
	point.xyzw.w = b;
	return (point);
}

t_3d	divide_3d(t_3d a, float b)
{
	t_3d r;

	r.xyz.x = a.xyz.x / b;
	r.xyz.y = a.xyz.y / b;
	r.xyz.z = a.xyz.z / b;
	return (r);
}

t_m4x4	columns3x3(t_3d x, t_3d y, t_3d z)
{
	t_m4x4 r;

	r = identity();
	r.e[0][0] = x.xyz.x;
	r.e[0][1] = y.xyz.x;
	r.e[0][2] = z.xyz.x;
	r.e[1][0] = x.xyz.y;
	r.e[1][1] = y.xyz.y;
	r.e[1][2] = z.xyz.y;
	r.e[2][0] = x.xyz.z;
	r.e[2][1] = y.xyz.z;
	r.e[2][2] = z.xyz.z;
	return (r);
}

t_m4x4	rows3x3(t_3d x, t_3d y, t_3d z)
{
	t_m4x4 r;

	r = identity();
	r.e[0][0] = x.xyz.x;
	r.e[0][1] = x.xyz.y;
	r.e[0][2] = x.xyz.z;
	r.e[1][0] = y.xyz.x;
	r.e[1][1] = y.xyz.y;
	r.e[1][2] = y.xyz.z;
	r.e[2][0] = z.xyz.x;
	r.e[2][1] = z.xyz.y;
	r.e[2][2] = z.xyz.z;
	return (r);
}
