/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:24:28 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/30 12:43:44 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Calculate from radians to degrees - (angle * 180 / PI32) degrees
*/

float	degree_radian(int degree)
{
	return (degree * PI32 / 180);
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

float	my_tan(float angle)
{
	float	r;

	r = tanf(angle);
	return (r);
}

float	my_asin(float angle)
{
	float	r;

	r = asinf(angle);
	return (r);
}

float	my_acos(float angle)
{
	float	r;

	r = acosf(angle);
	return (r);
}

float	my_atan(float angle)
{
	float	r;

	r = atanf(angle);
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
