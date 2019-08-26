/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:38:10 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/26 19:37:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	event_handler(t_wolf *wolf, int **map)
{
	t_player *p;

	p = &wolf->player;
	if (wolf->sdl.event.key.keysym.scancode == SDL_SCANCODE_F)
	{
		if (map[1][5] == 3
			&& (((int)p->position.x == 1 && (int)p->position.y == 6)
			|| ((int)p->position.x == 1 && (int)p->position.y == 4)))
			map[1][5] = 0;
		else if (map[1][5] == 0
			&& (((int)p->position.x == 1 && (int)p->position.y == 6)
			|| ((int)p->position.x == 1 && (int)p->position.y == 4)))
			map[1][5] = 3;

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

		else if (map[16][5] == 3
			&& (((int)p->position.x == 16 && (int)p->position.y == 6)
			|| ((int)p->position.x == 16 && (int)p->position.y == 4)))
			map[16][5] = 0;
		else if (map[16][5] == 0
			&& (((int)p->position.x == 16 && (int)p->position.y == 6)
			|| ((int)p->position.x == 16 && (int)p->position.y == 4)))
			map[16][5] = 3;

		else if (map[23][5] == 3
			&& (((int)p->position.x == 23 && (int)p->position.y == 6)
			|| ((int)p->position.x == 23 && (int)p->position.y == 4)))
			map[23][5] = 0;
		else if (map[23][5] == 0
			&& (((int)p->position.x == 23 && (int)p->position.y == 6)
			|| ((int)p->position.x == 23 && (int)p->position.y == 4)))
			map[23][5] = 3;

//////////////////////////////NS_DOORS/////////////////////////////////////

		else if (map[13][1] == 4
			&& (((int)p->position.x == 12 && (int)p->position.y == 1)
			|| ((int)p->position.x == 14 && (int)p->position.y == 1)))
			map[13][1] = 0;
		else if (map[23][1] == 0
			&& (((int)p->position.x == 12 && (int)p->position.y == 1)
			|| ((int)p->position.x == 14 && (int)p->position.y == 1)))
			map[13][1] = 4;

		else if (map[17][1] == 4
			&& (((int)p->position.x == 16 && (int)p->position.y == 1)
			|| ((int)p->position.x == 18 && (int)p->position.y == 1)))
			map[17][1] = 0;
		else if (map[17][1] == 0
			&& (((int)p->position.x == 16 && (int)p->position.y == 1)
			|| ((int)p->position.x == 18 && (int)p->position.y == 1)))
			map[17][1] = 4;
	}
}
