/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:26:36 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/16 23:47:46 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_4d	*int_to_points(t_fdf fdf)
{
	t_4d	*p;
	int		i;

	is_alloc(p = (t_4d*)ft_memalloc(sizeof(t_4d) * (fdf.obj.size + 1)));
	i = 0;
	while (i < fdf.obj.size)
	{
		p[i].xyzw.y = (((i / fdf.obj.len)) + 1);
		p[i].xyzw.x = (((i - (fdf.obj.len * p[i].xyzw.y))) + 1);
		p[i].xyzw.z = (fdf.obj.nb[i]);
		p[i].xyzw.w = 1;
		i++;
	}
	return (p);
}

int		calculate_scale(t_fdf fdf)
{
	fdf.scale = 1;
	initialize_cam(&fdf);
	if (transform(fdf.proj_matrix, fdf.p[0]).xyzw.x < 0
		|| transform(fdf.proj_matrix, fdf.p[0]).xyzw.y < 0)
	{
		while (transform(fdf.proj_matrix, fdf.p[1]).xyzw.x < 10
			|| transform(fdf.proj_matrix, fdf.p[1]).xyzw.y < 10)
		{
			fdf.scale -= 0.1f;
			initialize_cam(&fdf);
		}
	}
	else
	{
		while (transform(fdf.proj_matrix, fdf.p[0]).xyzw.x > 0
			&& transform(fdf.proj_matrix, fdf.p[0]).xyzw.y > 0)
		{
			fdf.scale += 0.1f;
			initialize_cam(&fdf);
		}
	}
	return (fdf.scale);
}

void	allocate_atois(t_fdf *fdf, char *line, t_2d_p *xy)
{
	ft_mem(&fdf->mem, sizeof(int));
	fdf->obj.nb = fdf->mem.m;
	fdf->obj.nb[xy->x] = (int)ft_atoi(line);
	xy->x++;
}

int		end_parse(t_fdf *fdf, int x)
{
	fdf->obj.size = x;
	return (1);
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
			is_alloc(NULL);
		free(line);
	}
	return (end_parse(fdf, xy.x));
}
