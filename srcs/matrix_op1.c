/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 05:28:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/24 13:16:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_m3x3	identity(void)
{
	t_m3x3	r;

	ft_bzero(&r, sizeof(r));
	r.e[0][0] = 1;
	r.e[1][1] = 1;
	r.e[2][2] = 1;
	return (r);
}

t_m3x3	scaling(float s)
{
	t_m3x3	r;

	ft_bzero(&r, sizeof(r));
	r.e[0][0] = s;
	r.e[1][1] = s;
	return (r);
}

t_m3x3	y_rot(float angle)
{
	float	c;
	float	s;
	t_m3x3	r;

	c = cos(angle);
	s = sin(angle);
	r = identity();
	r.e[1][1] = c;
	r.e[1][2] = -s;
	r.e[2][1] = s;
	r.e[2][2] = c;
	return (r);
}

t_m3x3	rot(float angle)
{
	float	c;
	float	s;
	t_m3x3	r;

	c = cos(angle);
	s = sin(angle);
	r = identity();
	r.e[0][0] = c;
	r.e[0][1] = s;
	r.e[1][0] = -s;
	r.e[1][1] = c;
	return (r);
}
