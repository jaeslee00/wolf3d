/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:40:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/16 23:45:51 by viccarau         ###   ########.fr       */
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

void	is_alloc(void *mem)
{
	if (mem == NULL)
	{
		ft_putendl("Allocation failed");
		exit(0);
	}
}

void	mem_init(t_fdf *fdf, t_img *img)
{
	ft_bzero(fdf, sizeof(fdf));
	ft_bzero(img, sizeof(img));
	fdf->multi = 1;
	is_alloc(fdf->mem.m = ft_memalloc((1024)));
	fdf->mem.tsize = (1024);
	fdf->mem.usize = sizeof(int);
	fdf->cam.zrot = 1;
}
