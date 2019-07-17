/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 00:51:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/17 20:31:25 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pers_keys(int keycode, t_fdf *fdf)
{
	if (keycode == SDL_SCANCODE_3)
	{
		if (fdf->flags & 0x4)
			fdf->flags &= ~(0x4);
		else
			fdf->flags |= 0x4;
	}
	if (keycode == SDL_SCANCODE_UP)
		fdf->offset.xyz.y -= 100 * fdf->multi;
	if (keycode == SDL_SCANCODE_DOWN)
		fdf->offset.xyz.y += 100 * fdf->multi;
	if (keycode == SDL_SCANCODE_LEFT)
		fdf->offset.xyz.x -= 100 * fdf->multi;
	if (keycode == SDL_SCANCODE_RIGHT)
		fdf->offset.xyz.x += 100 * fdf->multi;
	if (keycode == SDL_SCANCODE_Q)
		fdf->cam.zrot -= 1 * fdf->multi;
	if (keycode == SDL_SCANCODE_E)
		fdf->cam.zrot += 1 * fdf->multi;
}

void	key_to_camera(int keycode, t_fdf *fdf)
{
	if (keycode == SDL_SCANCODE_W)
		fdf->cam.pitch += 1* fdf->multi;
	if (keycode == SDL_SCANCODE_S)
		fdf->cam.pitch -= 1 * fdf->multi;
	if (keycode == SDL_SCANCODE_A)
		fdf->cam.orbit -= 1 * fdf->multi;
	if (keycode == SDL_SCANCODE_D)
		fdf->cam.orbit += 1 * fdf->multi;
	if (keycode == SDL_SCANCODE_MINUS)
		if (fdf->multi > 0.001f)
			fdf->multi *= 0.1f;
	if (keycode == SDL_SCANCODE_EQUALS)
		if (fdf->multi < 10)
			fdf->multi *= 10;
	if (keycode == SDL_SCANCODE_1)
	{
		if (fdf->zscale > 0)
			fdf->zscale -= 0.01f;
	}
	if (keycode == SDL_SCANCODE_2)
	{
		if (fdf->zscale < 100)
			fdf->zscale += 0.01f;
	}
}
