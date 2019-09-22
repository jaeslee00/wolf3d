/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:18:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/22 22:09:58 by viccarau         ###   ########.fr       */
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

static t_s32		is_valids(t_f32 x, t_f32 y)
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

static void			error_adjust(t_s32 *err, t_s32 *e2, t_ln *ln, t_2d_p *xy)
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

static void	drawline(t_wolf *wolf, t_pts pts, t_s32 nb)
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
				if (nb == 4)
					wolf->img[xy.x + (xy.y * W)] = 0x00FF00;
				else if (nb == 3)
					wolf->img[xy.x + (xy.y * W)] = 0xFF0000;
				else if (nb != 0)
					wolf->img[xy.x + (xy.y * W)] = 0x000000;
				else
					wolf->img[xy.x + (xy.y * W)] = 0xFFFFFF;
			}
			if (xy.x == (t_s32)pts.max.x && xy.y == (t_s32)pts.max.y)
				break ;
			e2 = err;
			error_adjust(&err, &e2, &ln, &xy);
		}
	}
}

t_2d	*init_points(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;
	t_s32	k;
	t_2d	*points;

	i = 10;
	k = 0;
	// // TODO(viccarau): 
	points = ft_memalloc(sizeof(t_2d) * wolf->obj.size);
//// TODO(viccarau): 
	ft_bzero(points, sizeof(t_2d) * wolf->obj.size);
	while (k < wolf->obj.size)
	{
		if (k % wolf->obj.w == 0)
{
		j = 10;
			i += 10;
		}
		points[k].x = j;
			points[k].y = i;
			j += 10;
			k++;
		}
	return (points);
}

void	draw_minimap(t_wolf *wolf)
{
	t_2d	*points;
	int		i;
	int		j;

i = 0;
	points = init_points(wolf);
	while (i < wolf->obj.size - 1)
	{
		if ((i + 1) % wolf->obj.w != 0)
		drawline(wolf, init_pts(points[i], points[i + 1]), wolf->obj.nb[i]);
		i++;
	}
	i = 0;
	j = 0;
	while (i < wolf->obj.size && j < wolf->obj.size)
	{
		j = i + wolf->obj.w;
		if (j < wolf->obj.size)
		drawline(wolf, init_pts(points[i], points[j]), wolf->obj.nb[i]);
		i++;
		}
}
