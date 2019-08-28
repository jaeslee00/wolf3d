/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:24:28 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/28 12:28:05 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Calculate from radians to degrees - (angle * 180 / PI32) degrees
*/

f64 fov_calculator(t_wolf *wolf)
{
	f64 fov;
	t_2d *pn;
	t_2d *d;

	d = &wolf->player.direction;
	pn = &wolf->player.plane;
	fov = (sqrt(pn->x * pn->x) + (pn->y * pn->y))
		/ (sqrt(d->x * d->x) + (d->y * d->y));
	fov = round(atan(fov) * 180 / PI32) * 2;
	return (fov);
}

f32	degree_radian(sint32 degree)
{
	return (degree * PI32 / 180);
}

f64	ft_abs(f64 x)
{
	if (x < 0)
		x = -x;
	return (x);
}

sint32		lerp(f64 a, f32 t, f64 b)
{
	sint32	result;

	result = (1.0f - t) * a + t * b;
	return (result);
}

sint32		rgb_lerp(sint32 color1, f32 t, sint32 color2)
{
	sint32	r;
	sint32	g;
	sint32	b;

	r = lerp(color1 / 0x10000, t, color2 / 0x10000);
	g = lerp(((color1 / 0x100) % 0x100), t, ((color2 / 0x100) % 0x100));
	b = lerp(color1 % 0x100, t, color2 % 0x100);
	return ((r << 16) + (g << 8) + b);
}

