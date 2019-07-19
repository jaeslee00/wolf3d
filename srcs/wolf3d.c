/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/18 01:12:41 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

int		my_function(int keycode, t_fdf *fdf)
{
	pers_keys(keycode, fdf);
	key_to_camera(keycode, fdf);
	if (keycode == SDL_SCANCODE_R)
	{
		fdf->cam.pitch = 0.01f;
		fdf->cam.orbit = 0.01f;
		fdf->zscale = 0.1f;
		ft_bzero(&fdf->offset, sizeof(fdf->offset));
	}
	if (keycode == SDL_SCANCODE_ESCAPE)
		is_alloc(NULL, *fdf, 0);
	if (keycode == SDL_SCANCODE_SPACE)
	{
		if (fdf->flags & ISO_PROJ)
			fdf->flags &= ~(ISO_PROJ);
		else
			fdf->flags |= ISO_PROJ + ORTH_PROJ;
	}
	return (1);
}

void	ft_mlx_init(t_fdf *fdf)
{
	int i;

	i = 0;
	SDL_Init(SDL_INIT_EVERYTHING);
	fdf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_RESIZABLE);
	fdf->str = ft_memalloc(W * H * sizeof(unsigned int));
	while (i < (W * H) / 2)
	{
		fdf->str[i] = 200;
		i++;
	}
	while (i < (W * H))
	{
		fdf->str[i] = 10000;
		i++;
	}

	//fdf->proj_matrix = final_projection(fdf);
}

int		main(int ac, char **av)
{
	int i;
	t_fdf	fdf;
	//int		fd;


	mem_init(&fdf);
	//fd = open(av[1], O_RDONLY);
	//fdf.str = ft_memalloc(W * H * sizeof(unsigned int));
	(void)av;
	(void)ac;
	ft_mlx_init(&fdf);
	fdf.sdl.renderer = SDL_CreateRenderer(fdf.sdl.win, -1, 0);
	fdf.sdl.texture = SDL_CreateTexture(fdf.sdl.renderer, SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STATIC, W, H);
	i = 0;
	while (1)
	{
		float avgFPS = i / ( SDL_GetTicks() / 1000.f );
		while (SDL_PollEvent(&fdf.sdl.event))
		{
			if (fdf.sdl.event.type == SDL_QUIT)
				exit(0);
			if (fdf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				exit(0);
			my_function(fdf.sdl.event.key.keysym.scancode, &fdf);
		}
		if (i % 100 == 0)
			printf("fps = %f\n", avgFPS);
		i++;
		if (i % 6 == 0)
		{
			//fdf.proj_matrix = final_projection(&fdf);
			//draw_to_img(fdf);
			SDL_UpdateTexture(fdf.sdl.texture, NULL, fdf.str, W * sizeof(unsigned int));
			SDL_RenderCopy(fdf.sdl.renderer, fdf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(fdf.sdl.renderer);
		}
	}
	return (0);
}
