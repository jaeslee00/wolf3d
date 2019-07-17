/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:26:36 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/17 23:49:20 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	allocate_atois(t_fdf *fdf, char *line, t_2d_p *xy)
{
	ft_mem(&fdf->mem, sizeof(int));
	fdf->obj.nb = fdf->mem.m;
	fdf->obj.nb[xy->x] = (int)ft_atoi(line);
	xy->x++;
}

int		tkneizer(int fd, t_fdf *fdf)
{
	char	*line;
	int		i;
	t_2d_p	xy;

	ft_bzero(&xy, sizeof(xy));
	while (get_next_line(fd, &line) > 0)
	{
		i = ft_skipspaces(line);
		allocate_atois(fdf, &line[i], &xy);
		while (line[i] != '\0')
		{
			if (!ft_iswhitespace(line[i + 1]) && line[i + 1] != '\0'
				&& ft_iswhitespace(line[i]))
				allocate_atois(fdf, &line[i], &xy);
			i++;
		}
		if (fdf->obj.len == 0)
			fdf->obj.len = xy.x;
		xy.y++;
		if ((xy.x) % fdf->obj.len != 0 || is_invalid(line))
			is_alloc(NULL, *fdf, -2);
		free(line);
	}
	fdf->obj.size = xy.x;
	return (1);
	}
