/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:40:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/20 04:24:29 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		is_invalid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != ',' &&
			!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	is_alloc(void *mem, t_wolf wolf, int error)
{
	(void)wolf;
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

void	mem_init(t_wolf *wolf)
{
	ft_bzero(&wolf[0], sizeof(*wolf));
	// NOTE(viccarau): This comments will help me see the size of my structures
	//				I'll optimize them by the way I need them
	
	//printf("size of wolf = %d\n", sizeof(*wolf));
	//printf("size of ind %d\n", sizeof(t_sdl) + sizeof(t_mem) + sizeof(t_obj) + sizeof(wolf->img) + sizeof(char));
	is_alloc(wolf->mem.m = ft_memalloc((3702644)), *wolf, -5);
	wolf->mem.tsize = 3702644;
	wolf->mem.usize = sizeof(int);
	}
