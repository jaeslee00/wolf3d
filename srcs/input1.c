/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 11:42:47 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/28 15:20:00 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	interaction_door(t_door *doors, sint8 **map, sint32 i)
{
	if (doors[i].flag & 1UL)
		{
			doors[i].flag &= ~(1UL);
			map[doors[i].pos.x][doors[i].pos.y] = 0;
		}
		else
		{
			doors[i].flag |= 1UL;
		if (doors[i].flag & 1UL << 1)
			map[doors[i].pos.x][doors[i].pos.y] = EW_DOOR;
else
			map[doors[i].pos.x][doors[i].pos.y] = NS_DOOR;
		}
	}

void	event_handler(t_wolf *wolf, sint8 **map, t_door *doors)
{
	t_player	*p;
	sint32		i;

	i = 0;
	p = &wolf->player;
	if (wolf->flag & 1UL << 7)
	{
		while (i < wolf->nbr_of_doors)
		{
			if (((sint32)p->pos.x == doors[i].pos.x
				&& (sint32)p->pos.y == doors[i].pos.y + 1)
				|| ((sint32)p->pos.x == doors[i].pos.x
					&& (sint32)p->pos.y == doors[i].pos.y - 1)
				|| ((sint32)p->pos.x == doors[i].pos.x + 1
					&& (sint32)p->pos.y == doors[i].pos.y)
				|| ((sint32)p->pos.x == doors[i].pos.x - 1
					&& (sint32)p->pos.y == doors[i].pos.y))
				interaction_door(doors, map, i);
			i++;
		}
		wolf->flag &= ~(1UL << 7);
	}
}

sint32		direction_movement(t_wolf *wolf, sint8 **map, sint32 framedelta)
{
	f32	time;
	t_player	*p;
	sint32	neg;

	p = &wolf->player;
	time = (f32)(framedelta / 200.f) * p->speed;
	if (wolf->flag & UP || wolf->flag & DOWN)
	{
		neg = (wolf->flag & UP) ? 1 : -1;
		if (map[(sint32)(p->pos.x + neg * (p->direction.x * (time + 0.2f)))][(sint32)(p->pos.y)] == 0)
			p->pos.x += neg * p->direction.x * time;
		if (map[(sint32)(p->pos.x)][(sint32)(p->pos.y + neg * (p->direction.y * (time + 0.2f)))] == 0)
			p->pos.y += neg * p->direction.y * time;
	}
	if (wolf->flag & RIGHT || wolf->flag & LEFT)
	{
		neg = (wolf->flag & RIGHT) ? 1 : -1;
		if (map[(sint32)(p->pos.x + neg * (p->plane.x * (time + 0.2f)))][(sint32)(p->pos.y)] == 0)
			p->pos.x += neg * (p->plane.x * time);
		if (map[(sint32)(p->pos.x)][(sint32)(p->pos.y + neg * (p->plane.y * (time + 0.2f)))] == 0)
			p->pos.y += neg * (p->plane.y * time);
	}
	return (1);
}
