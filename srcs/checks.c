/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:40:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/17 23:48:14 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_invalid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != 'x' && str[i]
			!= ',' && !(str[i] >= '0' && str[i] <= '9')
			&& !(str[i] >= 'a' && str[i] <= 'f') &&
			!(str[i] >= 'A' && str[i] <= 'F') && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

void	is_alloc(void *mem, t_fdf fdf, int error)
{
	(void)fdf;
	if (mem == NULL)
	{
		if (error == -2)
			ft_putstr_fd("Invalid map, not enough y values or invalid file\n", 2);
		if (error < 0 && error != -2)
			ft_putstr_fd("Malloc didn't want to give you memory. SAD\n", 2);
		if (error < 0)
			error = -1;
		exit(error);
	}
}

void	mem_init(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(fdf));
	fdf->multi = 1;
	is_alloc(fdf->mem.m = ft_memalloc((1024)), *fdf, -5);
	fdf->mem.tsize = (1024);
	fdf->mem.usize = sizeof(int);
	fdf->cam.zrot = 1;
}
