/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:26:36 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/27 00:56:00 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	 **int_to_tab(t_wolf *wolf)
{
	int i;
	int j;
	int k;
	char **tab;
	int lines;

	i = 0;
	k = 0;
	lines = (wolf->obj.size / wolf->obj.len);
	is_alloc(tab = ft_mem(&wolf->mem, sizeof(*tab) * lines), *wolf, -1);

	while (i < lines)
	{
		j = 0;
		is_alloc(tab[i] = ft_mem(&wolf->mem, sizeof(**tab) * (wolf->obj.len)), *wolf, -1);
		while (j < wolf->obj.len)
		{
			tab[i][j] = wolf->obj.nb[k];
				j++;
			k++;
		}
		i++;
	}
	return (tab);
}

void	allocate_atois(t_wolf *wolf, char *line, t_2d_p *xy)
{
	ft_mem(&wolf->mem, sizeof(char));
	wolf->obj.nb = wolf->mem.m;
	wolf->obj.nb[xy->x] = (char)ft_atoi(line);
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
	wolf->map = int_to_tab(wolf);
	return (1);
	}
