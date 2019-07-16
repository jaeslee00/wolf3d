/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:37:57 by viccarau          #+#    #+#             */
/*   Updated: 2019/06/16 02:53:00 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_ln	init_ln(t_pts pts)
{
	t_ln	ln;

	ln.d.x = ft_abs(pts.max.x - pts.min.x);
	ln.d.y = ft_abs(pts.max.y - pts.min.y);
	ln.s.x = pts.min.x < pts.max.x ? 1 : -1;
	ln.s.y = pts.min.y < pts.max.y ? 1 : -1;
	return (ln);
}

int		is_valid(float x, float y)
{
	if (((int)x + ((int)y * W)) >= (W * H)
		|| x <= 0 || y <= 0 || x >= W || y >= H)
		return (0);
	return (1);
}

float	range(float min, float max, float value)
{
	float	result;

	if ((value - min) == 0)
		return (0.5f);
	result = (value - min) / (max - min);
	if (result <= 0.1f)
		result = 0.1f;
	else if (result >= 1)
		result = 1;
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

void	range_finder(t_fdf *fdf)
{
	int	i;

	i = 0;
	if ((fdf->flags & 0x10) == 0)
	{
		fdf->l.min = fdf->obj.nb[0];
		fdf->l.max = fdf->obj.nb[0];
		while (i < fdf->obj.size)
		{
			if (fdf->obj.nb[i] < fdf->l.min)
				fdf->l.min = fdf->obj.nb[i];
			if (fdf->obj.nb[i] > fdf->l.max)
				fdf->l.max = fdf->obj.nb[i];
			i++;
		}
		fdf->flags |= 0x10;
	}
}
