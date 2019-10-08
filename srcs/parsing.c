/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:26:36 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/07 19:29:08 by viccarau         ###   ########.fr       */
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

t_s8		**int_to_tab(t_wolf *wolf)
{
	t_s32	i;
	t_s32	j;
	t_s32	k;
	t_s8	**tab;

	i = 0;
	k = 0;
	is_alloc(tab = ft_mem(&wolf->mem, sizeof(*tab) * wolf->obj.h), wolf, -1);
	while (i < wolf->obj.h)
	{
		j = 0;
		is_alloc(tab[i] = ft_mem(&wolf->mem,
			sizeof(**tab) * (wolf->obj.w)), wolf, -1);
		while (j < wolf->obj.w)
		{
			if (i == 0 || j == 0 ||
				j + 1 == wolf->obj.w || i + 1 == wolf->obj.h)
				wolf->obj.nb[k] = 1;
			tab[i][j] = wolf->obj.nb[k];
			j++;
			k++;
		}
		i++;
	}
	return (tab);
}

void		allocate_atois(t_wolf *wolf, t_s8 *line, t_2d_p *xy)
{
	is_alloc(ft_mem(&wolf->mem, sizeof(t_s8)), wolf, -1);
	wolf->obj.nb = wolf->mem.m;
	wolf->obj.nb[xy->x] = (t_s8)ft_atoi(line);
	xy->x++;
}

t_s32		tkneizer(t_s32 fd, t_wolf *wolf)
{
	t_s8	*line;
	t_s32	i;
	t_2d_p	xy;

	ft_bzero(&xy, sizeof(xy));
	while (get_next_line(fd, &line) > 0)
	{
		i = ft_skipspaces(line);
		allocate_atois(wolf, &line[i], &xy);
		while (line[i] != '\0')
		{
			if (!ft_iswhitespace(line[i + 1]) && line[i + 1] != '\0'
				&& ft_iswhitespace(line[i]))
				allocate_atois(wolf, &line[i], &xy);
			i++;
		}
		if (wolf->obj.w == 0)
			wolf->obj.w = xy.x;
		xy.y++;
		if (is_invalid(line) || (xy.x) % wolf->obj.w != 0)
			is_alloc(NULL, wolf, -2);
		free(line);
	}
	wolf->obj.size = xy.x;
	return (1);
}
