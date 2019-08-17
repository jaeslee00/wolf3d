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

int		my_function(int keycode, t_wolf *wolf, int **map)
{
	t_2d		old;
	t_player	*p;

	p = &wolf->player;
	if (keycode == SDL_SCANCODE_R)
		printf("\nYou pressed R\n\n");
	if (keycode == SDL_SCANCODE_ESCAPE)
		is_alloc(NULL, *wolf, 0);
	if (keycode == SDL_SCANCODE_W)
	{
if (map[(int)(p->position.x + p->direction.x * 0.05f)][(int)(p->position.y)] == 0)
			p->position.x += p->direction.x * p->speed;
		if (map[(int)(p->position.x)][(int)(p->position.y + p->direction.y * 0.05f)] == 0)
			p->position.y += p->direction.y * p->speed;
	}
	if (keycode == SDL_SCANCODE_S)
	{
		if (map[(int)(p->position.x - p->direction.x * 0.05f)][(int)(p->position.y)] == 0)
			p->position.x -= p->direction.x * p->speed;
		if (map[(int)(p->position.x)][(int)(p->position.y - p->direction.y * 0.05f)] == 0)
			p->position.y -= p->direction.y * p->speed;
	}
	if (keycode == SDL_SCANCODE_E)
	{
		if (map[(int)(p->position.x + p->plane.x * 0.05f)][(int)(p->position.y)] == 0)
			p->position.x += p->plane.x * 0.09f;
		if (map[(int)(p->position.x)][(int)(p->position.y + p->plane.y * 0.05f)] == 0)
			p->position.y += p->plane.y * 0.09f;
	}
	if (keycode == SDL_SCANCODE_Q)
	{
		if (map[(int)(p->position.x - p->plane.x * 0.05f)][(int)(p->position.y)] == 0)
			p->position.x -= p->plane.x * 0.09f;
		if (map[(int)(p->position.x)][(int)(p->position.y - p->plane.y * 0.05f)] == 0)
			p->position.y -= p->plane.y * 0.09f;
	}
	if (keycode == SDL_SCANCODE_A)
	{
		old.x = p->direction.x;
		p->direction.x = p->direction.x * cos(0.05f) - p->direction.y * sin(0.05f);
		p->direction.y = old.x * sin(0.05f) + p->direction.y * cos(0.05f);
		old.y = p->plane.x;
		p->plane.x = p->plane.x * cos(0.05f) - p->plane.y * sin(0.05f);
		p->plane.y = old.y * sin(0.05f) + p->plane.y * cos(0.05f);
	}
	if (keycode == SDL_SCANCODE_D)
	{
		old.x = p->direction.x;
		p->direction.x = p->direction.x * cos(-0.05f) - p->direction.y * sin(-0.05f);
		p->direction.y = old.x * sin(-0.05f) + p->direction.y * cos(-0.05f);
		old.y = p->plane.x;
		p->plane.x = p->plane.x * cos(-0.05f) - p->plane.y * sin(-0.05f);
		p->plane.y = old.y * sin(-0.05f) + p->plane.y * cos(-0.05f);
	}
// TODO(viccarau): Implement a FOV calculator by doing the dot product between direction and plane
// vectors, then the cos of the dot product is the angle of the FOV
// TODO(viccarau): Limit the FOV slider
if (keycode == SDL_SCANCODE_EQUALS)
	{
		p->direction.x *= 0.9f;
		p->direction.y *= 0.9f;
		p->speed *= 1.1f;
		}
	if (keycode == SDL_SCANCODE_MINUS)
	{
		p->direction.x *= 1.1f;
		p->direction.y *= 1.1f;
		p->speed *= 0.9f;
		}
printf("plane x\t%f , plane y\t%f\n", p->plane.x, p->plane.y);
	return (1);
}

void	ft_wolf_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED, W, H, 0);
	//SDL_WINDOW_FULLSCREEN
	wolf->img = ft_memalloc(W * H * sizeof(unsigned int));
	wolf->player.direction.x = -1;
	wolf->player.direction.y = 0;
	wolf->player.plane.x = 0;
	wolf->player.plane.y = 1;
	wolf->player.speed = 0.05f;
}

int		main(int ac, char **av)
{
	int		i;
	t_wolf	wolf;
	int		fd;
	//float	avg_fps;
	
	mem_init(&wolf);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("test.map", O_RDONLY);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
		print_map(wolf.map, wolf.obj, &wolf.player);
		//printf("\nplayer = %f, %f\n", wolf.player.position.x, wolf.player.position.y);
		ft_wolf_init(&wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
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
				my_function(wolf.sdl.event.key.keysym.scancode, &wolf, wolf.map);
				}
			ft_bzero(wolf.img, sizeof(unsigned int) * W * H);
			render(&wolf);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			i++;
			}
	return (0);
}
}
