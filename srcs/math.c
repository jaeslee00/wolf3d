/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:24:28 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/23 18:38:53 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_4d	point(float x, float y, float z, float w)
{
	t_4d p;

	p.xyzw.x = x;
	p.xyzw.y = y;
	p.xyzw.z = z;
	p.xyzw.w = w;
	return (p);
}

float	my_sin(float angle)
{
	float	r;

	r = sinf(angle);
	return (r);
}

float	my_cos(float angle)
{
	float	r;

	r = cosf(angle);
	return (r);
}

int		ft_abs(int x)
{
	if (x < 0)
		x = -x;
	return (x);
}

int		lerp(int a, float t, int b)
{
	int	result;

	result = (1.0f - t) * a + t * b;
	return (result);
}
