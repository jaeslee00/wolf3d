/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 00:51:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/23 18:51:45 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pers_keys(int keycode, t_wolf *wolf)
{
	if (keycode == SDL_SCANCODE_3)
	{
		if (wolf->flags & 0x4)
			wolf->flags &= ~(0x4);
		else
			wolf->flags |= 0x4;
	}
	if (keycode == SDL_SCANCODE_Q)
		wolf->cam.zrot -= 1 * wolf->multi;
	if (keycode == SDL_SCANCODE_E)
		wolf->cam.zrot += 1 * wolf->multi;
}

void	key_to_camera(int keycode, t_wolf *wolf)
{
	if (keycode == SDL_SCANCODE_W)
		wolf->cam.pitch += 1* wolf->multi;
	if (keycode == SDL_SCANCODE_S)
		wolf->cam.pitch -= 1 * wolf->multi;
	if (keycode == SDL_SCANCODE_A)
		wolf->cam.orbit -= 1 * wolf->multi;
	if (keycode == SDL_SCANCODE_D)
		wolf->cam.orbit += 1 * wolf->multi;
	if (keycode == SDL_SCANCODE_MINUS)
		if (wolf->multi > 0.001f)
			wolf->multi *= 0.1f;
	if (keycode == SDL_SCANCODE_EQUALS)
		if (wolf->multi < 10)
			wolf->multi *= 10;
	if (keycode == SDL_SCANCODE_1)
	{
		if (wolf->zscale > 0)
			wolf->zscale -= 0.01f;
	}
	if (keycode == SDL_SCANCODE_2)
	{
		if (wolf->zscale < 100)
			wolf->zscale += 0.01f;
	}
}
