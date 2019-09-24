/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:18:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/24 13:48:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
void	fill_rect(t_2d beg, t_2d end)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	size = 0;
}
*/

static t_s32	is_valids(t_f32 x, t_f32 y)
{
	if (((t_s32)x + ((t_s32)y * W)) >= (W * H)
		|| x <= 0 || y <= 0 || x >= W || y >= H)
		return (0);
	return (1);
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

static void	error_adjust(t_s32 *err, t_s32 *e2, t_ln *ln, t_2d_p *xy)
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

static t_ln	init_ln(t_pts pts)
{
	t_ln	ln;

	ln.d.x = ft_abs(pts.max.x - pts.min.x);
	ln.d.y = ft_abs(pts.max.y - pts.min.y);
	ln.s.x = pts.min.x < pts.max.x ? 1 : -1;
	ln.s.y = pts.min.y < pts.max.y ? 1 : -1;
	return (ln);
}

static void	drawline(t_wolf *wolf, t_pts pts, t_s32 nb, t_s32 nb1)
{
	t_2d_p	xy;
	t_s32		err;
	t_s32		e2;
	t_ln	ln;

	ln = init_ln(pts);
	err = (ln.d.x > ln.d.y ? ln.d.x : -ln.d.y) / 2;
	xy.x = (t_s32)round(pts.min.x);
	xy.y = (t_s32)round(pts.min.y);
	if (pts.min.x > 0 && pts.min.y > 0)
	{
		while (1)
		{
			if (is_valids(xy.x, xy.y))
			{
				if (nb == 4 || nb1 == 4)
					wolf->img[xy.x + (xy.y * W)] = 0x00BB00;
				else if (nb == 3 || nb1 == 3 || nb == 5 || nb1 == 5)
					wolf->img[xy.x + (xy.y * W)] = 0xBB0000;
				else if (nb != 0 || nb1 != 0)
					wolf->img[xy.x + (xy.y * W)] = 0x555555;
				else
					wolf->img[xy.x + (xy.y * W)] = 0x000000;
			}
			if (xy.x == (t_s32)pts.max.x && xy.y == (t_s32)pts.max.y)
				break ;
			e2 = err;
			error_adjust(&err, &e2, &ln, &xy);
		}
	}
}

void	init_points(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;
	t_s32	k;

	i = 0;
	k = 0;
	j = 0;
	while (k < wolf->obj.size)
	{
		if (k % wolf->obj.w == 0)
		{
			j = 0;
			i++;
		}
		wolf->p[k].x = j;
		wolf->p[k].y = i;
		j++;
		k++;
	}
}

t_m3x3	scale(t_f32	scale)
{
	t_m3x3	r;

	r = identity();
	r.e[0][0] = 1 * scale;
	r.e[1][1] = 1 * scale;
	r.e[2][2] = 1 * scale;
	return (r);
}

t_m3x3	translate(t_m3x3 a, t_2d	offset)
{
	t_m3x3	r;

	r = a;
	r.e[2][0] = offset.x;
	r.e[2][1] = offset.y;
	r.e[2][2] = 1;
	return (r);
}

void	draw_minimap(t_wolf *wolf)
{
t_s32	i;
	t_s32	j;
	t_s32	k;

	i = 0;
	k = 0;
	 wolf->proj_matrix = translate(wolf->proj_matrix, find_center(wolf));
	while (i < wolf->obj.size - 1)
	{
		if (i - wolf->obj.w > 0)
			k = i - wolf->obj.w;
		if ((i + 1) % wolf->obj.w != 0)
			drawline(wolf, init_pts(transform(wolf->proj_matrix, wolf->p[i]),
									transform(wolf->proj_matrix, wolf->p[i + 1])), wolf->obj.nb[i], wolf->obj.nb[k]);
		i++;
	}
	i = 0;
	j = 0;
	k = 0;
	while (i < wolf->obj.size && j < wolf->obj.size)
	{
		j = i + wolf->obj.w;
		if (i - 1 > 0)
			k = i - 1;
		if (j < wolf->obj.size)
			drawline(wolf, init_pts(transform(wolf->proj_matrix, wolf->p[i]),
									transform(wolf->proj_matrix, wolf->p[j])), wolf->obj.nb[i], wolf->obj.nb[k]);
		i++;
	}
}
