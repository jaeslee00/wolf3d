/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:24:28 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/08 17:09:18 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Calculate from radians to degrees - (angle * 180 / PI32) degrees
*/

t_f64		fov_calculator(t_wolf *wolf)
{
	t_f64		fov;
	t_2d	*pn;
	t_2d	*d;

	d = &wolf->player->direction;
	pn = &wolf->player->plane;
	fov = (sqrt(pn->x * pn->x) + (pn->y * pn->y))
		/ (sqrt(d->x * d->x) + (d->y * d->y));
	fov = round(atan(fov) * 180 / PI32) * 2;
	return (fov);
}

t_f32		degree_radian(t_s32 degree)
{
	return (degree * PI32 / 180);
}

t_f64		ft_abs(t_f64 x)
{
	if (x < 0)
		x = -x;
	return (x);
}

t_s32	lerp(t_f64 a, t_f32 t, t_f64 b)
{
	t_s32	result;

	result = (1.0f - t) * a + (t * b);
	return (result);
}

t_s32	rgb_lerp(t_s32 color1, t_f32 t, t_s32 color2)
{
	t_s32	r;
	t_s32	g;
	t_s32	b;

	r = lerp((color1 >> 16), t, (color2 >> 16));
	g = lerp(((color1 >> 8) & 0xFF), t, ((color2 >> 8) & 0xFF));
	b = lerp(color1 % 0x100, t, color2 % 0x100);
	return ((r << 16) + (g << 8) + b);
}
