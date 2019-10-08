/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:18:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 20:04:40 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static t_ln		init_ln(t_pts pts)
{
	t_ln	ln;

	ln.d.x = ft_abs(pts.max.x - pts.min.x);
	ln.d.y = ft_abs(pts.max.y - pts.min.y);
	ln.s.x = pts.min.x < pts.max.x ? 1 : -1;
	ln.s.y = pts.min.y < pts.max.y ? 1 : -1;
	return (ln);
}

static void		drawline(t_wolf *wolf, t_pts pts, t_s32 nb, t_s32 nb1)
{
	t_2d_p		xy;
	t_s32		err;
	t_s32		e2;
	t_ln		ln;

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
				color_picker(wolf, nb, nb1, xy);
			}
			if (xy.x == (t_s32)pts.max.x && xy.y == (t_s32)pts.max.y)
				break ;
			e2 = err;
			error_adjust(&err, &e2, &ln, &xy);
		}
	}
}

static void		draw_vertical_lines(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;
	t_s32	k;

	i = wolf->obj.w + 1;
	j = 0;
	k = 0;
	while (i < wolf->obj.size && j < wolf->obj.size)
	{
		j = i + wolf->obj.w;
		if (i - 1 > 0)
			k = i - 1;
		if (j < wolf->obj.size)
			drawline(wolf, init_pts(transform(wolf->proj_matrix, wolf->p[i]),
				transform(wolf->proj_matrix, wolf->p[j])),
					wolf->obj.nb[i], wolf->obj.nb[k]);
		i++;
		if (i % wolf->obj.w == 0)
			i++;
	}
}

void			draw_minimap(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;

	i = wolf->obj.w + 1;
	j = 0;
	wolf->proj_matrix = translate(wolf->proj_matrix, find_center(wolf));
	while (i < wolf->obj.size - 1)
	{
		if (i - wolf->obj.w > 0)
			j = i - wolf->obj.w;
		if ((i + 1) % wolf->obj.w != 0)
			drawline(wolf, init_pts(transform(wolf->proj_matrix, wolf->p[i]),
				transform(wolf->proj_matrix, wolf->p[i + 1])),
					wolf->obj.nb[i], wolf->obj.nb[j]);
		i++;
		if (i % wolf->obj.w == 0)
			i++;
	}
	draw_vertical_lines(wolf);
}
