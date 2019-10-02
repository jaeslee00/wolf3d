/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:40:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/02 14:46:28 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_s32		is_invalid(t_s8 *str)
{
	t_s32	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != ',' &&
			!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	is_alloc(void *mem, t_wolf *wolf, t_s32 error)
{
(void)wolf;
	if (mem == NULL)
	{
		printf("\ntsize = %zu\nusize = %zu \n", wolf->mem.tsize, wolf->mem.usize);
		if (error == -2)
			ft_putstr_fd("Invalid map, not enough y values or invalid file\n", 2);
		else if (error == -3)
			ft_putstr_fd("Texture(s) couldn't load\n", 2);
		else if (error == -1)
			ft_putstr_fd("Malloc didn't want to give you memory. SAD\n", 2);
		else if (error == -4)
			ft_putstr_fd("Texture isn't actually bmp file\n", 2);
		else if (error == -5)
			ft_putstr_fd("There is no player on the map, try putting a 9 on the map\n", 2);
		if (error < 0)
			error = -1;
		exit(error);
	}
}

// TODO(viccarau): Free memory at every exit
t_s32		mem_init(t_wolf *wolf, t_s32 ac, char **av)
{
	t_s32	fd;

	fd = 0;
	ft_bzero(&wolf[0], sizeof(*wolf));
	is_alloc(wolf->mem.m = ft_memalloc((1024 * 1024 * 200)), wolf, -5);
	wolf->mem.tsize = (1024 * 1024 * 200);
	wolf->mem.usize = sizeof(t_s32);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("wolf3d.map", O_RDONLY);
	return (fd);
}
