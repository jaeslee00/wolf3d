/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:40:07 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/09 18:00:51 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_empty_texture(t_wolf *wolf, t_texture *tex)
{
	tex->width = 64;
	tex->height = 64;
	is_alloc(tex->data = (t_u32*)ft_mem(&wolf->mem,
		64 * 64 * sizeof(t_u32)), wolf, -1);
}

t_s32	is_invalid(t_s8 *str)
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

void	free_sdl(t_sdl *sdl)
{
	if (sdl != NULL)
	{
		if (sdl->win != NULL)
			SDL_DestroyWindow(sdl->win);
		if (sdl->renderer != NULL)
			SDL_DestroyRenderer(sdl->renderer);
		if (sdl->texture != NULL)
			SDL_DestroyTexture(sdl->texture);
	}
}

void	is_alloc(void *mem, t_wolf *wolf, t_s32 error)
{
	if (mem == NULL)
	{
		free_sdl(wolf->sdl);
		if (error == -2)
			ft_putstr_fd("Invalid map, not enough y "
				"values or invalid file\n", 2);
		else if (error == -3)
			ft_putstr_fd("Texture(s) couldn't load\n", 2);
		else if (error == -1)
			ft_putstr_fd("Malloc didn't want to give you memory. SAD\n", 2);
		else if (error == -4)
			ft_putstr_fd("Texture isn't actually bmp file\n", 2);
		else if (error == -5)
			ft_putstr_fd("There is no player on the map,"
				"try putting a 9 on the map\n", 2);
		if (error < 0)
			error = -1;
		if (wolf->mem.m != NULL)
			free(wolf->mem.m);
		exit(error);
	}
}

t_s32	mem_init(t_wolf *wolf, t_s32 ac, char **av)
{
	t_s32	fd;

	fd = 0;
	ft_bzero(&wolf[0], sizeof(*wolf));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY | O_NONBLOCK | O_NOFOLLOW);
		if (!ft_strstr(av[1], ".map"))
			is_alloc(NULL, wolf, -2);
	}
	else
		fd = open("wolf3d.map", O_RDONLY | O_NONBLOCK | O_NOFOLLOW);
	if (fd > 0)
	{
		ft_bzero(&wolf->mem, sizeof(t_mem));
		is_alloc(wolf->mem.m = ft_memalloc((1024 * 1024 * 11)), wolf, -5);
		wolf->mem.tsize = (1024 * 1024 * 11);
		wolf->mem.usize = sizeof(t_s32);
	}
	else
		is_alloc(NULL, wolf, -2);
	return (fd);
}
