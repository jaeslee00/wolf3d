/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:10:22 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/09 12:17:33 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_m4x4	mx_mul(t_m4x4 a, t_m4x4 b)
{
	int		i;
	int		row;
	int		col;
	t_m4x4	re;

	ft_bzero(&re, sizeof(re));
	row = 0;
	while (row <= 3)
	{
		col = 0;
		while (col <= 3)
		{
			i = 0;
			while (i <= 3)
			{
				re.e[row][col] += a.e[row][i] * b.e[i][col];
				++i;
			}
			col++;
		}
		row++;
	}
	return (re);
}

t_4d	transform(t_m4x4 a, t_4d p)
{
	t_4d	r;

	r.xyzw.x = p.xyzw.x * a.e[0][0] + p.xyzw.y *
		a.e[0][1] + p.xyzw.z * a.e[0][2] + p.xyzw.w * a.e[0][3];
	r.xyzw.y = p.xyzw.x * a.e[1][0] + p.xyzw.y *
		a.e[1][1] + p.xyzw.z * a.e[1][2] + p.xyzw.w * a.e[1][3];
	r.xyzw.z = p.xyzw.x * a.e[2][0] + p.xyzw.y *
		a.e[2][1] + p.xyzw.z * a.e[2][2] + p.xyzw.w * a.e[2][3];
	r.xyzw.w = p.xyzw.x * a.e[3][0] + p.xyzw.y *
		a.e[3][1] + p.xyzw.z * a.e[3][2] + p.xyzw.w * a.e[3][3];
	return (r);
}

t_m4x4	translate(t_m4x4 a, t_3d t)
{
	t_m4x4 r;

	r = a;
	r.e[0][3] += t.xyz.x;
	r.e[1][3] += t.xyz.y;
	r.e[2][3] += t.xyz.z;
	return (r);
}

t_m4x4	translation(t_3d t)
{
	t_m4x4 r;

	r = identity();
	r.e[3][0] = t.xyz.x;
	r.e[3][1] = t.xyz.y;
	r.e[3][2] = t.xyz.z;
	return (r);
}

t_m4x4	z_rot(float angle)
{
	float	c;
	float	s;
	t_m4x4	r;

	r = identity();
	c = my_cos(angle);
	s = my_sin(angle);
	r.e[0][0] = c;
	r.e[0][1] = -s;
	r.e[1][0] = s;
	r.e[1][1] = c;
	return (r);
}
