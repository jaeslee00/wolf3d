/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 05:28:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 19:21:33 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

t_m3x3	scale(t_f32 scale)
{
	t_m3x3	r;

	r = identity();
	r.e[0][0] = 1 * scale;
	r.e[1][1] = 1 * scale;
	r.e[2][2] = 1 * scale;
	return (r);
}

t_m3x3	translate(t_m3x3 a, t_2d offset)
{
	t_m3x3	r;

	r = a;
	r.e[2][0] = offset.x;
	r.e[2][1] = offset.y;
	r.e[2][2] = 1;
	return (r);
}
