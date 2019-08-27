/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:38:10 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/27 06:18:57 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	interaction_door(t_door *doors, sint8 **map, sint32 i)
{
	if (doors[i].flag == 0b00)
	{
		doors[i].flag = 0b01;
		map[doors[i].pos.x][doors[i].pos.y] = 0;
	}
	else if (doors[i].flag == 0b01)
	{
		doors[i].flag = 0b00;
		map[doors[i].pos.x][doors[i].pos.y] = 3;
	}
	else if (doors[i].flag == 0b10)
	{
		doors[i].flag = 0b11;
		map[doors[i].pos.x][doors[i].pos.y] = 0;
	}
	else if (doors[i].flag == 0b11)
	{
		doors[i].flag = 0b10;
		map[doors[i].pos.x][doors[i].pos.y] = 5;
	}
}

void	event_handler(t_wolf *wolf, sint8 **map, t_door *doors)
{
	t_player *p;
	sint32		i;

	i = 0;
	p = &wolf->player;
	if (wolf->sdl.event.key.keysym.scancode == SDL_SCANCODE_F)
	{
		while (i < wolf->nbr_of_doors)
		{
			if ( ((sint32)p->pos.x == doors[i].pos.x && (sint32)p->pos.y == doors[i].pos.y + 1)
			|| ((sint32)p->pos.x == doors[i].pos.x && (sint32)p->pos.y == doors[i].pos.y - 1)
			|| ((sint32)p->pos.x == doors[i].pos.x + 1 && (sint32)p->pos.y == doors[i].pos.y)
			|| ((sint32)p->pos.x == doors[i].pos.x - 1 && (sint32)p->pos.y == doors[i].pos.y) )
				interaction_door(doors, map, i);
			i++;
		}
	}
}
