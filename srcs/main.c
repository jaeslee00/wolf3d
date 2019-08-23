/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */

/*   Updated: 2019/07/30 12:13:41 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
 if (event.key.keysym.scancode == SDL_SCANCODE_Q)
 {
  old.x = p->direction.x;
  p->direction.x = p->direction.x * cos(0.2f) - p->direction.y * sin(0.2f);
  p->direction.y = old.x * sin(0.2f) + p->direction.y * cos(0.2f);
  old.y = p->plane.x;
  p->plane.x = p->plane.x * cos(0.2f) - p->plane.y * sin(0.2f);
  p->plane.y = old.y * sin(0.2f) + p->plane.y * cos(0.2f);
 }
 if (event.key.keysym.scancode == SDL_SCANCODE_E)
 {
  old.x = p->direction.x;
  p->direction.x = p->direction.x * cos(-0.2f) - p->direction.y * sin(-0.2f);
  p->direction.y = old.x * sin(-0.2f) + p->direction.y * cos(-0.2f);
  old.y = p->plane.x;
  p->plane.x = p->plane.x * cos(-0.2f) - p->plane.y * sin(-0.2f);
  p->plane.y = old.y * sin(-0.2f) + p->plane.y * cos(-0.2f);
 }
*/


void	ft_wolf_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
	wolf->img = ft_mem(&wolf->mem, W * H * sizeof(unsigned int));
	wolf->player.direction.x = -1;
	wolf->player.direction.y = 0;
	wolf->player.plane.x = 0;
	wolf->player.plane.y = 1;
	wolf->player.speed = 0.02f;
	wolf->flag = 0;
	}

void	ceiling(unsigned int *img)
{
	int x;
	int y;
	int y1;
	 float color;
	 
	color = 0x333300;
	x = 0;
	y = 0;
	y1 = (H / 2) << 6;
	while (y < H / 2)
	{
		x = 0;
		while (x < W)
		{
			img[x + y * W] = color;
			color = y1 / 4;
			x++;
		}
		y++;
		y1--;
	}
	y1 = (H / 8);
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			img[x + y * W] = color;
			color = y1 / 4;
			x++;
		}
		y++;
		y1++;
		}
		}

int		main(int ac, char **av)
{
	int		i;
	t_wolf	wolf;
	int		fd;
	int frames[61];
	
	mem_init(&wolf);
		if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("test.map", O_RDONLY);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
print_map(wolf.map, wolf.obj, &wolf.player);
		ft_wolf_init(&wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		i = 0;
		ft_bzero(frames, sizeof(int) * 61);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		while (1)
		{
			frames[i] = SDL_GetTicks();
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
is_alloc(NULL, wolf, 0);
				set_flag(&wolf, wolf.sdl.event);
					}
					direction_movement(&wolf, wolf.map);
			//ft_bzero(wolf.img, sizeof(unsigned int) * W * H);
			ceiling(wolf.img);
			render(&wolf);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			ft_frametimes(frames, &i);
			i++;
		}
	}
	return (0);
}
