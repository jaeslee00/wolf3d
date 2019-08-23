/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 03:51:22 by viccarau          #+#    #+#             */

/*   Updated: 2019/08/15 03:54:56 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int print_map(int **map, t_obj obj, t_player *player)
{
	int	lines;
	int	i;
	int	j;

	lines = (obj.size / obj.len);
	i = 0;
	//printf("\n \t0  1  2  3  4  5  6  7  8  9  10 11\n\n");
	while (i < lines)
	{
		j = 0;
		while (j < obj.len)
		{
			//if (j == 0)
				//printf("%d\t", i);
			if (map[i][j] == 2)
			{
				map[i][j] = 0;
				player->position.x = i;
				player->position.y = j;
			}
			//printf("%d  ", map[i][j]);
			j++;
		}
		i++;
		//printf("\n");
	}
	return (0);
}
