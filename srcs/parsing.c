/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:26:36 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/30 15:44:06 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int **int_to_tab(t_obj obj)
{
	int i;
	int j;
	int k;
	int **tab;
	int lines;

	i = 0;
	k = 0;
	lines = (obj.size / obj.len);
	tab = ft_memalloc(sizeof(*tab) * lines);
	while (i < lines)
	{
		j = 0;
		tab[i] = ft_memalloc(sizeof(**tab) * (obj.len));
		while (j < obj.len)
		{
			tab[i][j] = obj.nb[k];
				j++;
			k++;
		}
		i++;
	}
	return (tab);
}

void	allocate_atois(t_wolf *wolf, char *line, t_2d_p *xy)
{
	ft_mem(&wolf->mem, sizeof(int));
	wolf->obj.nb = wolf->mem.m;
	wolf->obj.nb[xy->x] = (int)ft_atoi(line);
	xy->x++;
}

int		tkneizer(int fd, t_wolf *wolf)
{
	char	*line;
	int		i;
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
		if (wolf->obj.len == 0)
			wolf->obj.len = xy.x;
		xy.y++;
		if ((xy.x) % wolf->obj.len != 0 || is_invalid(line))
			is_alloc(NULL, *wolf, -2);
		free(line);
	}
	wolf->obj.size = xy.x;
	return (1);
	}
