/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:36:04 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/28 23:36:04 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf3d.h"

void		count_entities(t_s8 **map, t_obj obj, t_entity *entity)
{
	t_s32	i;
	t_s32	j;

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

static t_u8	get_player_pos(t_wolf* wolf, t_s32 i, t_s32 j)
{
	t_player	*p;

	p = wolf->player;
	if (wolf->map[i][j] == 9)
	{
		wolf->map[i][j] = 0;
		p->pos.x = j + 0.5f;
		p->pos.y = i + 0.5f;
	}
	else if (wolf->map[i][j] == 0 && (p->pos.x == 0 || p->pos.y == 0))
	{
		p->pos.x = j + 0.5f;
		p->pos.y = i + 0.5f;
	}
	else
		return (0);
	return (1);
}

static t_u8	parse_doors(t_wolf *wolf, t_s32 i, t_s32 j, t_s32 *k)
{
	if (wolf->map[i][j] == 3 || wolf->map[i][j] == 5)
	{
		if (wolf->map[i][j] == 3)
			wolf->doors[*k].flag |= 1UL << 1;
		wolf->doors[*k].flag |= 1UL;
		wolf->doors[*k].pos.x = j;
		wolf->doors[*k].pos.y = i;
		*k += 1;
		wolf->nbr_of_doors = *k;
	}
	else
		return (0);
	return (1);
}

static void	parse_items(t_wolf *wolf, t_s32 i, t_s32 j, t_s32 *k)
{
	if (wolf->map[i][j] == 4)
	{
		wolf->entity->item[*k].pos.x = (t_f32)j + 0.5f;
		wolf->entity->item[*k].pos.y = (t_f32)i + 0.5f;
		*k += 1;
	}
}

t_s32		parse_map(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;
	t_s32	k;
	t_s32	w;

	i = 0;
	k = 0;
	w = 0;
	while (i < wolf->obj.h)
	{
		j = 0;
		while (j < wolf->obj.w)
		{
			if (!get_player_pos(wolf, i, j))
				parse_items(wolf, i, j, &w);
			parse_doors(wolf, i, j, &k);
			j++;
		}
		i++;
	}
	if (wolf->player->pos.x == 0 || wolf->player->pos.y == 0)
		is_alloc(NULL, wolf, -5);
	return (0);
}
