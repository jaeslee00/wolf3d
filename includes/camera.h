/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:02:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/05/09 11:58:36 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "fdf.h"
# include "draw.h"

typedef struct	s_cam
{
	t_3d	offset;
	t_3d	shift;
	float	zrot;
	float	pitch;
	float	orbit;
	float	dolly;
	float	focal_length;
	float	near_clip;
	float	far_clip;
}				t_cam;

typedef struct	s_camloc
{
	t_3d	camx;
	t_3d	camy;
	t_3d	camz;
	t_3d	camp;
}				t_camloc;

float			inner(t_2d a, t_2d b);
t_4d			vector4(t_3d p, float b);
t_3d			divide_3d(t_3d a, float b);
t_m4x4			columns3x3(t_3d x, t_3d y, t_3d z);
t_m4x4			rows3x3(t_3d x, t_3d y, t_3d z);

#endif
