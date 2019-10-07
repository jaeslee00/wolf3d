/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:41:13 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 19:49:57 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_s32	is_valids(t_f32 x, t_f32 y)
{
	if (((t_s32)x + ((t_s32)y * W)) >= (W * H)
		|| x <= 0 || y <= 0 || x >= W || y >= H)
		return (0);
	return (1);
}

t_pts	init_pts(t_2d xy0, t_2d xy1)
{
	t_pts	pts;

	pts.min.x = round(xy0.x);
	pts.max.x = round(xy1.x);
	pts.min.y = round(xy0.y);
	pts.max.y = round(xy1.y);
	return (pts);
}

void	error_adjust(t_s32 *err, t_s32 *e2, t_ln *ln, t_2d_p *xy)
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

t_2d	find_center(t_wolf *wolf)
{
	t_s32	center;
	t_2d	offset;

	if (wolf->obj.size % 2 == 0)
		center = round(wolf->obj.size / 2) + round((wolf->obj.w) / 2);
	else
		center = round(wolf->obj.size / 2);
	(void)center;
	offset.x = ((W / 2) - transform(wolf->proj_matrix, wolf->player->pos).x);
	offset.y = ((H / 2) - transform(wolf->proj_matrix, wolf->player->pos).y);
	return (offset);
}

void	init_points(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;
	t_s32	k;

	i = 0;
	k = 1;
	j = 1;
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
