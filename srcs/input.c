/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:02:53 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/08 16:16:12 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		check_key(t_wolf *wolf, SDL_Event event,
				SDL_Scancode key, t_s32 bit)
{
	if (event.key.keysym.scancode == key)
	{
		if (event.type == SDL_KEYDOWN)
			wolf->flag |= bit;
		else
			wolf->flag &= ~(bit);
	}
}

void		set_flag(t_wolf *wolf, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_1
		&& !(wolf->flag & 1UL << 9))
		wolf->flag |= 1UL << 10;
	if (event.key.keysym.scancode == SDL_SCANCODE_2
		&& !(wolf->flag & 1UL << 9))
		wolf->flag &= ~(1UL << 10);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		wolf->flag |= 1UL << 9;
	check_key(wolf, event, SDL_SCANCODE_W, 1UL);
	check_key(wolf, event, SDL_SCANCODE_S, 1UL << 1);
	check_key(wolf, event, SDL_SCANCODE_A, 1UL << 2);
	check_key(wolf, event, SDL_SCANCODE_D, 1UL << 3);
	check_key(wolf, event, SDL_SCANCODE_UP, 1UL);
	check_key(wolf, event, SDL_SCANCODE_DOWN, 1UL << 1);
	check_key(wolf, event, SDL_SCANCODE_LEFT, 1UL << 2);
	check_key(wolf, event, SDL_SCANCODE_RIGHT, 1UL << 3);
	check_key(wolf, event, SDL_SCANCODE_EQUALS, 1UL << 4);
	check_key(wolf, event, SDL_SCANCODE_MINUS, 1UL << 5);
	check_key(wolf, event, SDL_SCANCODE_LSHIFT, 1UL << 6);
	non_repeat_key(wolf, event);
}

void		check_flag(t_wolf *wolf, t_s8 **map)
{
	t_f32		fov;
	t_player	*p;

	p = wolf->player;
	fov = fov_calculator(wolf);
	direction_movement(wolf, map);
	if (wolf->flag & 1UL << 4 && fov < 120.0f)
	{
		p->direction.x *= 0.99f;
		p->direction.y *= 0.99f;
		ft_putnbr((int)fov);
		ft_putchar('\n');
	}
	if (wolf->flag & 1UL << 5 && fov > 60.0f)
	{
		p->direction.x *= 1.01f;
		p->direction.y *= 1.01f;
		ft_putnbr((int)fov);
		ft_putchar('\n');
	}
}

static void	view_limit(t_s32 *view, t_s32 yrelative)
{
	*view += yrelative;
	if (*view > H / 2)
		*view = H / 2;
	else if (*view < -H / 2)
		*view = -H / 2;
}

void		mouse_movement(t_wolf *wolf, SDL_Event event)
{
	t_2d		old;
	t_f64		motion;
	t_f32		cosine;
	t_f32		sine;
	t_player	*p;

	p = wolf->player;
	if (event.type == SDL_MOUSEMOTION)
	{
		motion = (t_f64)(event.motion.xrel * 0.001f);
		view_limit(&wolf->view, (t_s32)event.motion.yrel);
		cosine = cos(motion);
		sine = sin(motion);
		p->m->rotation += motion;
		p->m->rotation = fmod(p->m->rotation, 2.0f * PI32);
		old.x = p->direction.x;
		p->direction.x = p->direction.x * cosine - p->direction.y * sine;
		p->direction.y = old.x * sine + p->direction.y * cosine;
		old.y = p->plane.x;
		p->plane.x = p->plane.x * cosine - p->plane.y * sine;
		p->plane.y = old.y * sine + p->plane.y * cosine;
	}
}
