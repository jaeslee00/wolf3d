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

sint32 print_map(sint8 **map, t_obj obj, t_player *player, t_door *doors, t_wolf *wolf)
{
	sint32	lines;
	sint32	i;
	sint32	j;
	sint32 k;

	lines = (obj.size / obj.len);
	i = 0;
	k = 0;
	//printf("\n \t0  1  2  3  4  5  6  7  8  9  10 11\n\n");
	while (i < lines)
	{
		j = 0;
		while (j < obj.len)
		{
			//if (j == 0)
				//printf("%d\t", i);
			if (map[i][j] == 9)
			{
				map[i][j] = 0;
				player->pos.x = i;
				player->pos.y = j;
			}
			else if (map[i][j] == 3 || map[i][j] == 5)
			{
				if (map[i][j] == 3)
					doors[k].flag |= 1UL << 1;
				doors[k].flag |= 1UL;
				doors[k].pos.x = i;
				doors[k].pos.y = j;
				k++;
				wolf->nbr_of_doors = k;
			}
			j++;
		}
		i++;
		}
	return (0);
}

void ft_frametimes(sint32 *frames, sint32 *count)
{
	sint32	j;

	if (*count == 60)
	{
		*count = 1;
		j = 0;
		while (*count <= 59)
		{
			ft_putnbr(frames[*count] - frames[j]);
			ft_putstr(" ms ");
			*count += 1;
			if (*count % 12 == 0)
			ft_putchar('\n');
			j++;
		}
		ft_bzero(frames, sizeof(sint32) * 61);
		ft_putchar('\n');
		*count = -1;
	}
}
