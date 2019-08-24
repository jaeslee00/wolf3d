/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 03:05:39 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/25 00:39:24 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*

 NOTE:(viccarau)	I created the function check_key that generalizes the setting
 of flags. Movement is changed but too complicated to explain in this comment;

	- Added running by pressing SHIFT
*/

void	mouse_movement(t_wolf *wolf, SDL_Event event)
{
	t_2d		old;
	double motion;
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
	t_player	*p;
	double fov;

	p = &wolf->player;
	fov = fov_calculator(wolf);
	mouse_movement(wolf, event);
	if (event.key.keysym.scancode == SDL_SCANCODE_EQUALS && fov < 120.0f)
	{
		p->direction.x *= 0.99f;
		p->direction.y *= 0.99f;
		printf("fov = %f\n", fov);
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_MINUS && fov > 60)
	{
		p->direction.x *= 1.01f;
		p->direction.y *= 1.01f;
		printf("fov = %f\n", fov);
	}
	check_key(wolf, event, SDL_SCANCODE_W, UP);
	check_key(wolf, event, SDL_SCANCODE_S, DOWN);
	check_key(wolf, event, SDL_SCANCODE_A, LEFT);
	check_key(wolf, event, SDL_SCANCODE_D, RIGHT);
	if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
	{
		if (event.type == SDL_KEYDOWN)
			wolf->player.speed = 0.04f;
		else
			wolf->player.speed = 0.03f;
	}
}

int		direction_movement(t_wolf *wolf, int **map)
{
	t_player	*p;

	p = &wolf->player;
	if (wolf->flag & 1UL)
	{
		if (map[(int)(p->position.x + p->direction.x * (p->speed + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x += p->direction.x * p->speed;
		if (map[(int)(p->position.x)][(int)(p->position.y + p->direction.y * (p->speed + 0.2f))] == 0)
			p->position.y += p->direction.y * p->speed;
	}
	if (wolf->flag & 1UL << 1)
	{
		if (map[(int)(p->position.x - p->direction.x * (p->speed + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x -= p->direction.x * p->speed;
		if (map[(int)(p->position.x)][(int)(p->position.y - p->direction.y * (p->speed + 0.2f))] == 0)
			p->position.y -= p->direction.y * p->speed;
	}
	if (wolf->flag & 1UL << 2)
	{
		if (map[(int)(p->position.x + p->plane.x * (p->speed + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x += p->plane.x * p->speed;
		if (map[(int)(p->position.x)][(int)(p->position.y + p->plane.y * (p->speed + 0.2f))] == 0)
			p->position.y += p->plane.y * p->speed;
	}
	if (wolf->flag & 1UL << 3)
	{
		if (map[(int)(p->position.x - p->plane.x * (p->speed + 0.2f))][(int)(p->position.y)] == 0)
			p->position.x -= p->plane.x * p->speed;
		if (map[(int)(p->position.x)][(int)(p->position.y - p->plane.y * (p->speed + 0.2f))] == 0)
			p->position.y -= p->plane.y * p->speed;
	}
	return (1);
}
