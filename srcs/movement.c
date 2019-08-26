/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 03:05:39 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/26 17:12:32 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mouse_movement(t_wolf *wolf, SDL_Event event)
{
	t_2d		old;
	double	motion;
	t_player	*p;

	p = &wolf->player;
	if (event.type == SDL_MOUSEMOTION)
	{
		motion = -(double)(event.motion.xrel * 0.001f);
		old.x = p->direction.x;
		p->direction.x = p->direction.x * cos(motion) - p->direction.y * sin(motion);
		p->direction.y = old.x * sin(motion) + p->direction.y * cos(motion);
		old.y = p->plane.x;
		p->plane.x = p->plane.x * cos(motion) - p->plane.y * sin(motion);
		p->plane.y = old.y * sin(motion) + p->plane.y * cos(motion);
	}
}

void	check_key(t_wolf *wolf, SDL_Event event, SDL_Scancode key, int bit)
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
	mouse_movement(wolf, event);
	check_key(wolf, event, SDL_SCANCODE_W, UP);
	check_key(wolf, event, SDL_SCANCODE_S, DOWN);
	check_key(wolf, event, SDL_SCANCODE_A, LEFT);
	check_key(wolf, event, SDL_SCANCODE_D, RIGHT);
	check_key(wolf, event, SDL_SCANCODE_EQUALS, 1UL << 4);
	check_key(wolf, event, SDL_SCANCODE_MINUS, 1UL << 5);
	check_key(wolf, event, SDL_SCANCODE_LSHIFT, 1UL << 6);
	check_key(wolf, event, SDL_SCANCODE_F, 1UL << 7);
}

int		direction_movement(t_wolf *wolf, int **map, int framedelta)
{
	float	time;
	float	fov;
	t_player	*p;

	fov = fov_calculator(wolf);
	p = &wolf->player;
	time = (float)(framedelta / 200.f) * p->speed;
	if (wolf->flag & UP)
	{
		if (map[(int)(p->position.x + p->direction.x * (time + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x += p->direction.x * time;
		if (map[(int)(p->position.x)][(int)(p->position.y + p->direction.y * (time + 0.2f))] == 0)
			p->position.y += p->direction.y * time;
	}
	if (wolf->flag & DOWN)
	{
		if (map[(int)(p->position.x - p->direction.x * (time + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x -= p->direction.x * time;
		if (map[(int)(p->position.x)][(int)(p->position.y - p->direction.y * (time + 0.2f))] == 0)
			p->position.y -= p->direction.y * time;
	}
	if (wolf->flag & RIGHT)
	{
		if (map[(int)(p->position.x + p->plane.x * (time + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x += p->plane.x * time;
		if (map[(int)(p->position.x)][(int)(p->position.y + p->plane.y * (time + 0.2f))] == 0)
			p->position.y += p->plane.y * time;
	}
	if (wolf->flag & LEFT)
	{
		if (map[(int)(p->position.x - p->plane.x * (time + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x -= p->plane.x * time;
		if (map[(int)(p->position.x)][(int)(p->position.y - p->plane.y * (time + 0.2f))] == 0)
			p->position.y -= p->plane.y * time;
	}
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
	//NOTE (jae) : testing open/closing doors coordinates are hardcoded lul some keys cannot be like movement i think!! dunno where to change though
	if (wolf->flag & 1UL << 7)
	{
		if (map[5][5] == 3
			&& (((int)p->position.x == 5 && (int)p->position.y == 6)
			|| ((int)p->position.x == 5 && (int)p->position.y == 4)))
			map[5][5] = 0;
		else if (map[5][5] == 0
			&& (((int)p->position.x == 5 && (int)p->position.y == 6)
			|| ((int)p->position.x == 5 && (int)p->position.y == 4)))
			map[5][5] = 3;
		else if (map[9][5] == 3
			&& (((int)p->position.x == 9 && (int)p->position.y == 6)
			|| ((int)p->position.x == 9 && (int)p->position.y == 4)))
			map[9][5] = 0;
		else if (map[9][5] == 0
			&& (((int)p->position.x == 9 && (int)p->position.y == 6)
			|| ((int)p->position.x == 9 && (int)p->position.y == 4)))
			map[9][5] = 3;
	}
	return (1);
}
