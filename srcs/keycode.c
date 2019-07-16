/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 00:51:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/16 23:47:19 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
void	ui_instructions(t_fdf fdf)
{
	char	*kappa;

	kappa = ft_itoa(fdf.multi * 1000);
	mi(fdf, 40, 55, "Press arrow keys for map offset and press R for reset");
	mi(fdf, 40, 70, "Use space to toggle between isometric "
	"orthogonal projection");
	mi(fdf, 40, 85, "Press 1 or 2 to increase - decrease z values");
	mi(fdf, 40, 100, "Press 3 to toggle the text");
	mi(fdf, 40, 115, "Press '-' or '=' to decrease or increase multiplyer - ");
	mi(fdf, 40, 130, kappa);
	mi(fdf, 40, 40, "Use the mouse scroll for zoom in or out");
	if ((fdf.flags & ISO_PROJ) == 0)
	{
		mi(fdf, 100, 1, "ORTHOGONAL PROJECTION");
		mi(fdf, 40, 20, "Use AD WS QE for map roatation on x, y, z axes");
	}
	else
	{
		mi(fdf, 100, 1, "ISOMETRIC PERSPECTIVE");
		mi(fdf, 40, 20, "Can't rotate in isometric perspective");
	}
	free(kappa);
}

void	pers_keys(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_3)
	{
		if (fdf->flags & 0x4)
			fdf->flags &= ~(0x4);
		else
			fdf->flags |= 0x4;
	}
	if (keycode == KEY_UP)
		fdf->offset.xyz.y -= 100 * fdf->multi;
	if (keycode == KEY_DOWN)
		fdf->offset.xyz.y += 100 * fdf->multi;
	if (keycode == KEY_LEFT)
		fdf->offset.xyz.x -= 100 * fdf->multi;
	if (keycode == KEY_RIGHT)
		fdf->offset.xyz.x += 100 * fdf->multi;
	if (keycode == KEY_Q)
		fdf->cam.zrot -= 1 * fdf->multi;
	if (keycode == KEY_E)
		fdf->cam.zrot += 1 * fdf->multi;
}

void	key_to_camera(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W)
		fdf->cam.pitch += 1 * fdf->multi;
	if (keycode == KEY_S)
		fdf->cam.pitch -= 1 * fdf->multi;
	if (keycode == KEY_A)
		fdf->cam.orbit -= 1 * fdf->multi;
	if (keycode == KEY_D)
		fdf->cam.orbit += 1 * fdf->multi;
	if (keycode == KEY_MINUS)
		if (fdf->multi > 0.001f)
			fdf->multi *= 0.1f;
	if (keycode == KEY_EQUAL)
		if (fdf->multi < 10)
			fdf->multi *= 10;
	if (keycode == KEY_1)
	{
		if (fdf->zscale > 0)
			fdf->zscale -= 0.01f;
	}
	if (keycode == KEY_2)
	{
		if (fdf->zscale < 100)
			fdf->zscale += 0.01f;
	}
}
*/