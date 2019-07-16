/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:30:59 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/09 12:12:53 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_m4x4	identity(void)
{
	t_m4x4	r;

	ft_bzero(&r, sizeof(r));
	r.e[0][0] = 1;
	r.e[1][1] = 1;
	r.e[2][2] = 1;
	r.e[3][3] = 1;
	return (r);
}

t_m4x4	scaling(float s)
{
	t_m4x4	r;

	ft_bzero(&r, sizeof(r));
	r.e[0][0] = s;
	r.e[1][1] = s;
	r.e[2][2] = s;
	r.e[3][3] = s;
	return (r);
}

t_m4x4	z_scaling(float s)
{
	t_m4x4	r;

	r = identity();
	r.e[2][2] = s;
	r.e[3][3] = s;
	return (r);
}

t_m4x4	x_rot(float angle)
{
	t_m4x4	r;

	r = identity();
	r.e[1][1] = my_cos(angle);
	r.e[1][2] = -(my_sin(angle));
	r.e[2][1] = my_sin(angle);
	r.e[2][2] = my_cos(angle);
	return (r);
}

t_m4x4	y_rot(float angle)
{
	float	c;
	float	s;
	t_m4x4	r;

	c = my_cos(angle);
	s = my_sin(angle);
	r = identity();
	r.e[0][0] = c;
	r.e[0][2] = s;
	r.e[2][0] = -s;
	r.e[2][2] = c;
	return (r);
}
