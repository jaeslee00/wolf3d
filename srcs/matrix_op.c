/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 05:28:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/24 13:16:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_m3x3	identity(void)
{
	t_m3x3	r;

	ft_bzero(&r, sizeof(r));
	r.e[0][0] = 1;
	r.e[1][1] = 1;
	r.e[2][2] = 1;
	return (r);
}

t_m3x3	scaling(float s)
{
	t_m3x3	r;

	ft_bzero(&r, sizeof(r));
	r.e[0][0] = s;
	r.e[1][1] = s;
	return (r);
}

t_m3x3	y_rot(float angle)
{
	float	c;
	float	s;
	t_m3x3	r;

	c = cos(angle);
	s = sin(angle);
	r = identity();
	r.e[1][1] = c;
	r.e[1][2] = -s;
	r.e[2][1] = s;
	r.e[2][2] = c;
	return (r);
}

t_m3x3	rot(float angle)
{
	float	c;
	float	s;
	t_m3x3	r;

	c = cos(angle);
	s = sin(angle);
	r = identity();
	r.e[0][0] = c;
	r.e[0][1] = s;
	r.e[1][0] = -s;
	r.e[1][1] = c;
	return (r);
}

t_m3x3	mx_mul(t_m3x3 a, t_m3x3 b)
{
	int		i;
	int		row;
	int		col;
	t_m3x3	re;

	ft_bzero(&re, sizeof(re));
	row = 0;
	while (row < 3)
	{
		col = 0;
		while (col < 3)
		{
			i = 0;
			while (i < 3)
			{
				re.e[row][col] += a.e[row][i] * b.e[i][col];
				++i;
			}
			col++;
		}
		row++;
	}
	return (re);
}

t_2d	transform(t_m3x3 a, t_2d p)
{
	t_2d	r;

	r.x = p.x * a.e[0][0] + p.y *
		a.e[0][1] + a.e[2][0];
	r.y = p.x * a.e[1][0] + p.y *
		a.e[1][1] + a.e[2][1];
	return (r);
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
