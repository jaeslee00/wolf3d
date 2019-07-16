/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:52:36 by viccarau          #+#    #+#             */
/*   Updated: 2019/06/05 03:13:48 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		color_picker(t_fdf *fdf, int j, int k)
{
	float	color;
	int		median;

	median = ((fdf->obj.nb[j] + fdf->obj.nb[k]) / 2);
	range_finder(fdf);
	color = range(fdf->l.min, fdf->l.max, median);
	if (fdf->l.min == fdf->l.max)
		color = 0.5f;
	if (fdf->obj.nb[j] <= 0)
	{
		color = range(fdf->l.min, 0, median);
		return (rgb_lerp(0x0000A0, color, 0x7272FE));
	}
	else if (fdf->obj.nb[j] > 0 && fdf->obj.nb[j] < (fdf->l.max / 10))
	{
		color = range(0, fdf->l.max / 10, median);
		return (rgb_lerp(0x00FF00, color, 0x66AA00));
	}
	else if (fdf->obj.nb[j] < (fdf->l.max * 0.6f))
	{
		color = range(fdf->l.max / 10, fdf->l.max * 0.6f, median);
		return (rgb_lerp(0x666A00, color, 0x272800));
	}
	return (rgb_lerp(0x272800, color, 0xFFFFFF));
}

void			error_adjust(int *err, int *e2, t_ln *ln, t_2d_p *xy)
{
	if (*e2 > -ln->d.x)
	{
		*err -= ln->d.y;
		xy->x += ln->s.x;
	}
	if (*e2 < ln->d.y)
	{
		*err += ln->d.x;
		xy->y += ln->s.y;
	}
}

void			drawline(t_pts pts, t_fdf *fdf, int i, int j)
{
	t_2d_p	xy;
	int		err;
	int		e2;
	t_ln	ln;

	ln = init_ln(pts);
	err = (ln.d.x > ln.d.y ? ln.d.x : -ln.d.y) / 2;
	xy.x = (int)round(pts.min.x);
	xy.y = (int)round(pts.min.y);
	while (1)
	{
		if (is_valid(xy.x, xy.y))
			fdf->str[xy.x + (xy.y * W)] = color_picker(fdf, i, j);
		if (xy.x == (int)pts.max.x && xy.y == (int)pts.max.y)
			break ;
		e2 = err;
		error_adjust(&err, &e2, &ln, &xy);
	}
}

static t_pts	init_pts(t_2d xy0, t_2d xy1)
{
	t_pts	pts;

	pts.min.x = round(xy0.x);
	pts.max.x = round(xy1.x);
	pts.min.y = round(xy0.y);
	pts.max.y = round(xy1.y);
	return (pts);
}

void			draw_to_img(t_fdf fdf)
{
	int		i;
	int		j;

	i = 0;
	ft_bzero(fdf.str, W * H * sizeof(int));
	fdf.proj_matrix = translate(fdf.proj_matrix, find_center(fdf));
	while (i < fdf.obj.size)
	{
		if ((i + 1) % fdf.obj.len != 0)
			drawline(init_pts(transform(fdf.proj_matrix, fdf.p[i]).xy.xy,
							  transform(fdf.proj_matrix, fdf.p[i + 1]).xy.xy), &fdf, i, i + 1);
		i++;
	}
	i = 0;
	j = 0;
	while (i < (fdf.obj.size))
	{
		j = i + fdf.obj.len;
		if (j < fdf.obj.size)
			drawline(init_pts(transform(fdf.proj_matrix, fdf.p[i]).xy.xy,
							  transform(fdf.proj_matrix, fdf.p[j]).xy.xy), &fdf, i, j);
		i++;
	}
}
