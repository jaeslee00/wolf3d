/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:46:12 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/07 15:51:53 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

typedef struct	s_m4x4
{
	float		e[4][4];
}				t_m4x4;

typedef struct	s_2d
{
			float	x;
			float	y;
}				t_2d;

typedef union	u_3d
{
	struct
	{
		t_2d	xy;
		float	ignored0;
	}			xy0;
	struct
	{
		float	x;
		float	y;
		float	z;
	}			xyz;
	float		f_3d[3];
}				t_3d;

typedef union	u_4d
{
	struct
	{
		t_2d	xy;
		float	ignored0;
		float	ignored1;
	}			xy;
	struct
	{
		t_3d	xyz;
		float	ignored2;
	}			xyz;
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	}			xyzw;
	float		f_4d[4];
}				t_4d;

#endif
