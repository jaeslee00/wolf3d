/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:38:10 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/27 01:49:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void interaction_door(t_door *doors, char **map, int i)
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

void	event_handler(t_wolf *wolf, char **map, t_door *doors)
{
	t_player *p;
	int		i;

	i = 0;
	p = &wolf->player;
	if (wolf->sdl.event.key.keysym.scancode == SDL_SCANCODE_F)
	{
		while (i < wolf->nbr_of_doors)
		{
			if ( ((int)p->pos.x == doors[i].pos.x && (int)p->pos.y == doors[i].pos.y + 1)
			|| ((int)p->pos.x == doors[i].pos.x && (int)p->pos.y == doors[i].pos.y - 1)
			|| ((int)p->pos.x == doors[i].pos.x + 1 && (int)p->pos.y == doors[i].pos.y)
			|| ((int)p->pos.x == doors[i].pos.x - 1 && (int)p->pos.y == doors[i].pos.y) )
			{
				interaction_door(doors, map, i);
			}
			i++;
		}
	}
// 		if (map[1][5] == 3
// 			&& (((int)p->pos.x == 1 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 1 && (int)p->pos.y == 4)))
// 			map[1][5] = 0;
// 		else if (map[1][5] == 0
// 			&& (((int)p->pos.x == 1 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 1 && (int)p->pos.y == 4)))
// 			map[1][5] = 3;

// 		else if (map[5][5] == 3
// 			&& (((int)p->pos.x == 5 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 5 && (int)p->pos.y == 4)))
// 			map[5][5] = 0;
// 		else if (map[5][5] == 0
// 			&& (((int)p->pos.x == 5 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 5 && (int)p->pos.y == 4)))
// 			map[5][5] = 3;

// 		else if (map[9][5] == 3
// 			&& (((int)p->pos.x == 9 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 9 && (int)p->pos.y == 4)))
// 			map[9][5] = 0;
// 		else if (map[9][5] == 0
// 			&& (((int)p->pos.x == 9 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 9 && (int)p->pos.y == 4)))
// 			map[9][5] = 3;

// 		else if (map[16][5] == 3
// 			&& (((int)p->pos.x == 16 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 16 && (int)p->pos.y == 4)))
// 			map[16][5] = 0;
// 		else if (map[16][5] == 0
// 			&& (((int)p->pos.x == 16 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 16 && (int)p->pos.y == 4)))
// 			map[16][5] = 3;

// 		else if (map[23][5] == 3
// 			&& (((int)p->pos.x == 23 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 23 && (int)p->pos.y == 4)))
// 			map[23][5] = 0;
// 		else if (map[23][5] == 0
// 			&& (((int)p->pos.x == 23 && (int)p->pos.y == 6)
// 			|| ((int)p->pos.x == 23 && (int)p->pos.y == 4)))
// 			map[23][5] = 3;

// //////////////////////////////NS_DOORS/////////////////////////////////////

// 		else if (map[13][1] == 4
// 			&& (((int)p->pos.x == 12 && (int)p->pos.y == 1)
// 			|| ((int)p->pos.x == 14 && (int)p->pos.y == 1)))
// 			map[13][1] = 0;
// 		else if (map[23][1] == 0
// 			&& (((int)p->pos.x == 12 && (int)p->pos.y == 1)
// 			|| ((int)p->pos.x == 14 && (int)p->pos.y == 1)))
// 			map[13][1] = 4;

// 		else if (map[17][1] == 4
// 			&& (((int)p->pos.x == 16 && (int)p->pos.y == 1)
// 			|| ((int)p->pos.x == 18 && (int)p->pos.y == 1)))
// 			map[17][1] = 0;
// 		else if (map[17][1] == 0
// 			&& (((int)p->pos.x == 16 && (int)p->pos.y == 1)
// 			|| ((int)p->pos.x == 18 && (int)p->pos.y == 1)))
// 			map[17][1] = 4;
// 	}
}
