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

int print_map(int **map, t_obj obj, t_player *player)
{
	int	lines;
	int	i;
	int	j;

	lines = (obj.size / obj.len);
	i = 0;
	printf("\n \t0  1  2  3  4  5  6  7  8  9  10 11\n\n");
	while (i < lines)
	{
		j = 0;
		while (j < obj.len)
		{
			 if (j == 0)
				printf("%d\t", i);
			if (map[i][j] == 2)
			{
				player->position.x = (i * 64) + 32;
				player->position.y = (j * 64) + 32;
			}
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
	if (keycode == SDL_SCANCODE_R)
		printf("\nYou pressed R\n\n");
	if (keycode == SDL_SCANCODE_ESCAPE)
		is_alloc(NULL, *wolf, 0);
	return (1);
}

void	ft_wolf_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
	wolf->img = ft_memalloc(W * H * sizeof(unsigned int));
	wolf->player.arc = W / 12;
	wolf->player.distance = 426;
	wolf->player.height = 32;
	wolf->player.speed = 16;
}

int		main(int ac, char **av)
{
	int		i;
	t_wolf	wolf;
	int		fd;
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	//float	avg_fps;
	wolf.player.direction.x = 0;
	wolf.player.direction.y = -1.0f;
	//p.plane.x = 0;
	//p.plane.y = 80;

	mem_init(&wolf);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("test.map", O_RDONLY);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
		print_map(wolf.map, wolf.obj, &wolf.player);
		printf("\nplayer = %d, %d\n", wolf.player.position.x, wolf.player.position.y);
		ft_wolf_init(&wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		//ft_raycast(&wolf);
		i = 0;
		while (1)
		{
			//avg_fps = i / ( SDL_GetTicks() / 1000.f );
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					exit(0);
				my_function(wolf.sdl.event.key.keysym.scancode, &wolf);
				//if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_A)
					//wolf.player.arc -= 5;
				//if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_D)
					//wolf.player.arc += 5;
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_W)
					wolf.player.position.x += 1;
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_S)
					wolf.player.position.x -= 1;
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_A)
					{
					double oldDirX = dirX;
						dirX = dirX * cos(0.01f) - dirY * sin(0.01f);
						dirY = oldDirX * sin(0.01f) + dirY * cos(0.01f);
						double oldPlaneX = planeX;
						planeX = planeX * cos(0.01f) - planeY * sin(0.01f);
						planeY = oldPlaneX * sin(0.01f) + planeY * cos(0.01f);
					}
					if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_D)
				{
					double oldDirX = dirX;
					dirX = dirX * cos(-0.01f) - dirY * sin(-0.01f);
					dirY = oldDirX * sin(-0.01f) + dirY * cos(-0.01f);
					double oldPlaneX = planeX;
					planeX = planeX * cos(-0.01f) - planeY * sin(-0.01f);
					planeY = oldPlaneX * sin(-0.01f) + planeY * cos(-0.01f);
				}
					}
			ft_bzero(wolf.img, sizeof(unsigned int) * W * H);
			render(&wolf, dirX, dirY, planeX, planeY);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			i++;
			}
	return (0);
}
}
