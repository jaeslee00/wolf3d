/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:24:28 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/24 23:45:02 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Calculate from radians to degrees - (angle * 180 / PI32) degrees
*/

double fov_calculator(t_wolf *wolf)
{
	double fov;
	t_2d *pn;
	t_2d *d;

	d = &wolf->player.direction;
	pn = &wolf->player.plane;
	fov = (sqrt(pn->x * pn->x) + (pn->y * pn->y)) / (sqrt(d->x * d->x) + (d->y * d->y));
	fov = round(atan(fov) * 180 / PI32) * 2;
	return (fov);
}

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

double	ft_abs(double x)
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

int		rgb_lerp(int color1, float t, int color2)
{
	int	r;
	int	g;
	int	b;

	r = lerp(color1 / 0x10000, t, color2 / 0x10000);
	g = lerp(((color1 / 0x100) % 0x100), t, ((color2 / 0x100) % 0x100));
	b = lerp(color1 % 0x100, t, color2 % 0x100);
	return ((r * 0x10000) + (g * 0x100) + b);
}

