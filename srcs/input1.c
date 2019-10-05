/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:42:47 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/09 18:22:23 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	interaction_door(t_door *doors, t_s8 **map, t_s32 i)
{
	if (doors[i].flag & 1UL)
	{
		doors[i].flag &= ~(1UL);
		map[doors[i].pos.y][doors[i].pos.x] = 0;
	}
	else
	{
		doors[i].flag |= 1UL;
		map[doors[i].pos.y][doors[i].pos.x] = 3;
	}
}

void	event_handler(t_wolf *wolf, t_s8 **map, t_door *doors)
{
	t_player	*p;
	t_u32		i;

	i = 0;
	p = wolf->player;
	if (wolf->flag & 1UL << 7)
	{
		while (i < wolf->nbr_of_doors)
		{
			if (((t_s32)p->pos.x == doors[i].pos.x
				&& (t_s32)p->pos.y == doors[i].pos.y + 1)
				|| ((t_s32)p->pos.x == doors[i].pos.x
					&& (t_s32)p->pos.y == doors[i].pos.y - 1)
				|| ((t_s32)p->pos.x == doors[i].pos.x + 1
					&& (t_s32)p->pos.y == doors[i].pos.y)
				|| ((t_s32)p->pos.x == doors[i].pos.x - 1
					&& (t_s32)p->pos.y == doors[i].pos.y))
				interaction_door(doors, map, i);
			i++;
		}
		wolf->flag &= ~(1UL << 7);
	}
}

static t_u8	max_mag(t_wolf *wolf, t_player *p)
{
	if (wolf->flag & 1UL << 6)
	{
		if (sqrt(p->accel.x * p->accel.x + p->accel.y * p->accel.y) < 1.5)
			return (1);
	}
	else
	{
		if (sqrt(p->accel.x * p->accel.x + p->accel.y * p->accel.y) < 1)
			return (1);
	}
	return (0);
}

static void	acceleration_movement(t_wolf *wolf, t_player *p)
{
	t_s32	neg;
	t_f32	speed;

	speed = 0.05f;
	if (max_mag(wolf, p))
	{
		if (wolf->flag & 1UL || wolf->flag & 1UL << 1)
		{
			neg = (wolf->flag & 1UL) ? 1 : -1;
			p->accel.x += neg * p->direction.x * speed;
			p->accel.y += neg * p->direction.y * speed;
		}
		if (wolf->flag & 1UL << 2|| wolf->flag & 1UL << 3)
		{
			neg = (wolf->flag & 1UL << 3) ? 1 : -1;
			p->accel.x += neg * p->plane.x * speed;
			p->accel.y += neg * p->plane.y * speed;
		}
	}
	p->accel.x -= p->accel.x / 20;
	p->accel.y -= p->accel.y / 20;
}

t_s32		direction_movement(t_wolf *wolf, t_s8 **map)
{
	t_2d	temp;
	t_player	*p;

	p = wolf->player;
	acceleration_movement(wolf, p);
	temp.x = p->accel.x * (t_f32)(wolf->deltatime / 200.f);
	temp.y = p->accel.y * (t_f32)(wolf->deltatime / 200.f);
	if (map[(t_s32)(p->pos.y)][(t_s32)(p->pos.x + temp.x + 0.1f)] == 0 &&
		map[(t_s32)(p->pos.y + temp.y + 0.1f)][(t_s32)(p->pos.x)] == 0 &&
		map[(t_s32)(p->pos.y)][(t_s32)(p->pos.x + temp.x - 0.1f)] == 0 &&
		map[(t_s32)(p->pos.y + temp.y - 0.1f)][(t_s32)(p->pos.x)] == 0)
	{
		p->pos.x += temp.x;
		p->pos.y += temp.y;
	}
	return (1);
}
