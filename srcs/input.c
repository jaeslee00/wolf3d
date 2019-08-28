/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:02:53 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/28 14:34:47 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check_key(t_wolf *wolf, SDL_Event event, SDL_Scancode key, sint32 bit)
{
	if (event.key.keysym.scancode == key)
	{
		if (event.type == SDL_KEYDOWN)
			wolf->flag |= bit;
		else
			wolf->flag &= ~(bit);
	}
}

void	set_flag(t_wolf *wolf, SDL_Event event)
{
	check_key(wolf, event, SDL_SCANCODE_W, UP);
	check_key(wolf, event, SDL_SCANCODE_S, DOWN);
	check_key(wolf, event, SDL_SCANCODE_A, LEFT);
	check_key(wolf, event, SDL_SCANCODE_D, RIGHT);
	check_key(wolf, event, SDL_SCANCODE_EQUALS, 1UL << 4);
	check_key(wolf, event, SDL_SCANCODE_MINUS, 1UL << 5);
	check_key(wolf, event, SDL_SCANCODE_LSHIFT, 1UL << 6);
	if (wolf->sdl.event.key.repeat == 0)
	{
		check_key(wolf, event, SDL_SCANCODE_E, 1UL << 7);
		if (wolf->sdl.event.key.keysym.scancode == SDL_SCANCODE_TAB)
			if (wolf->sdl.event.type == SDL_KEYDOWN)
			wolf->flag ^= 1UL << 8;
	}
}

void	check_flag(t_wolf *wolf, sint8 **map, sint32 framedelta)
{
	f32	fov;
	t_player	*p;

	p = &wolf->player;
	fov = fov_calculator(wolf);
	direction_movement(wolf, map, framedelta);
	if (wolf->flag & 1UL << 4 && fov < 120.0f)
	{
		p->direction.x *= 0.99f;
		p->direction.y *= 0.99f;
		printf("fov = %f\n", fov);
	}
	if (wolf->flag & 1UL << 5 && fov > 60.0f)
	{
		p->direction.x *= 1.01f;
		p->direction.y *= 1.01f;
		printf("fov = %f\n", fov);
	}
	if (wolf->flag & 1UL << 6)
		wolf->player.speed = 1.5f;
	else
		wolf->player.speed = 1;
}

void	mouse_movement(t_wolf *wolf, SDL_Event event)
{
	t_2d		old;
	f64	motion;
	t_player	*p;

	p = &wolf->player;
	if (event.type == SDL_MOUSEMOTION)
	{
		motion = -(f64)(event.motion.xrel * 0.001f);
		old.x = p->direction.x;
		p->direction.x = p->direction.x * cos(motion) - p->direction.y * sin(motion);
		p->direction.y = old.x * sin(motion) + p->direction.y * cos(motion);
		old.y = p->plane.x;
		p->plane.x = p->plane.x * cos(motion) - p->plane.y * sin(motion);
		p->plane.y = old.y * sin(motion) + p->plane.y * cos(motion);
	}
}
