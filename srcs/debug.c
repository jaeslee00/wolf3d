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

void	count_entities(sint8 **map, t_obj obj, t_entity *entity)
{
	sint32	i;
	sint32	j;
	
	i = 0;
	while (i < obj.h)
	{
		j = 0;
		while (j < obj.w)
		{
			if (map[i][j] == 4)
				entity->nbr_of_entities++;
			j++;
		}
		i++;
	}
}

sint32 print_map(sint8 **map, t_obj obj, t_player *player, t_door *doors, t_wolf *wolf)
{
	sint32	i;
	sint32	j;
	sint32	k;
	sint32	w;

	i = 0;
	k = 0;
	w = 0;
	while (i < obj.h)
	{
		j = 0;
		while (j < obj.w)
		{
			if (map[i][j] == 9)
			{
				map[i][j] = 0;
				player->pos.x = j;
				player->pos.y = i;
			}
			else if (map[i][j] == 4)
			{
				wolf->entity->item[w].pos.x = (f32)j + 0.5f;
				wolf->entity->item[w].pos.y = (f32)i + 0.5f;
				w++;
			}
			else if (map[i][j] == 3 || map[i][j] == 5)
			{
				if (map[i][j] == 3)
					doors[k].flag |= 1UL << 1;
				doors[k].flag |= 1UL;
				doors[k].pos.x = j;
				doors[k].pos.y = i;
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
		ft_memset(frames, 0, sizeof(sint32) * 61);
		ft_putchar('\n');
		*count = -1;
	}
}
