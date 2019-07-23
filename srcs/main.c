/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/23 20:27:24 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int print_map(int **map, t_obj obj)
{
	int lines;
	int i;
	int j;

	lines = (obj.size / obj.len);
i = 0;
	printf("\t0  1  2  3  4  5  6  7  8  9  10 11\n\n");
	while (i < lines)
	{
		j = 0;
		while (j < obj.len)
		{
			if (j == 0)
				printf("%d\t", i);
			printf("%d  ", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
return (0);
}

int		my_function(int keycode, t_wolf *wolf)
{
	pers_keys(keycode, wolf);
	key_to_camera(keycode, wolf);
	if (keycode == SDL_SCANCODE_R)
	{
		wolf->cam.pitch = 0.01f;
		wolf->cam.orbit = 0.01f;
		wolf->zscale = 0.1f;
		}
	if (keycode == SDL_SCANCODE_ESCAPE)
		is_alloc(NULL, *wolf, 0);
	if (keycode == SDL_SCANCODE_SPACE)
	{
		if (wolf->flags & ISO_PROJ)
			wolf->flags &= ~(ISO_PROJ);
		else
			wolf->flags |= ISO_PROJ + ORTH_PROJ;
	}
	return (1);
}

void	ft_mlx_init(t_wolf *wolf)
{
	int i;

	i = 0;
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_RESIZABLE);
	wolf->img = ft_memalloc(W * H * sizeof(unsigned int));
	while (i < (W * H) / 2)
	{
		wolf->img[i] = 200;
		i++;
	}
	while (i < (W * H))
	{
		wolf->img[i] = 10000;
		i++;
	}

	//wolf->proj_matrix = final_projection(wolf);
}

int		main(int ac, char **av)
{
	int i;
	t_wolf	wolf;
	int		fd;
	float avg_fps;

	mem_init(&wolf);
	//wolf.img = ft_memalloc(W * H * sizeof(unsigned int));
	fd = open(av[1], O_RDONLY | O_NONBLOCK);
	if (ac == 2 && fd > 0)
{
		tkneizer(fd, &wolf);
		print_map(int_to_tab(wolf.obj), wolf.obj);
		ft_mlx_init(&wolf);
	wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
	wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer, SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STATIC, W, H);
	i = 0;
	while (1)
	{
		avg_fps = i / ( SDL_GetTicks() / 1000.f );
		while (SDL_PollEvent(&wolf.sdl.event))
		{
			if (wolf.sdl.event.type == SDL_QUIT)
				exit(0);
			if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				exit(0);
			my_function(wolf.sdl.event.key.keysym.scancode, &wolf);
		}
		if (i % 100 == 0)
			printf("fps = %f\n", avg_fps);
		i++;
		if (i % 6 == 0)
		{
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
		}
	}
	}
	return (0);
}
