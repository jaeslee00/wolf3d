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

// TODO(viccarau): Limit the FOV slider

void	set_flag(t_wolf *wolf, SDL_Event event)
{
	//state = SDL_GetKeyboardState(NULL);
	t_2d		old;
	t_player	*p;
	double motion;

	p = &wolf->player;
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
	if (event.type == SDL_MOUSEMOTION)
	{
		motion = -(double)(event.motion.xrel * 0.001f);
		old.x = p->direction.x;
		p->direction.x = p->direction.x * cos(motion) - p->direction.y * sin(motion);
		p->direction.y = old.x * sin(motion) + p->direction.y * cos(motion);
		old.y = p->plane.x;
		p->plane.x = p->plane.x * cos(motion) - p->plane.y * sin(motion);
		p->plane.y = old.y * sin(motion) + p->plane.y * cos(motion);
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_W)
		{
		if (event.type == SDL_KEYDOWN)
		{
			wolf->flag &= ~(1UL << 1);
			wolf->flag |= 1UL;
		}
else
			wolf->flag &= ~(1UL);
			}
	if (event.key.keysym.scancode == SDL_SCANCODE_S)
	{
		if (event.type == SDL_KEYDOWN)
		{
		wolf->flag &= ~(1UL);
				  wolf->flag |= 1UL << 1;
	}
else
			wolf->flag &= ~(1UL << 1);
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_D)
	{
		if (event.type == SDL_KEYDOWN)
		{
		wolf->flag &= ~(1UL << 3);
				  wolf->flag |= 1UL << 2;
		}
			else
				wolf->flag &= ~(1UL << 2);
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_A)
	{
		if (event.type == SDL_KEYDOWN)
		{
		wolf->flag &= ~(1UL << 2);
		wolf->flag |= 1UL << 3;
		}
else
		wolf->flag &= ~(1UL << 3);
	}
	}

// TODO(viccarau): I want a circle colision from the player to the walls

// TODO(viccarau): Implement a FOV calculator by doing the dot product between direction and plane
// vectors, then the cos of the dot product is the angle of the FOV

int		my_function(SDL_Event event, t_wolf *wolf, int **map)
{
	t_player	*p;
	
	p = &wolf->player;
	if (wolf->flag & 1UL)
		{
			if (map[(int)(p->position.x + p->direction.x * p->speed)][(int)(p->position.y)] == 0)
				p->position.x += p->direction.x * p->speed;
			if (map[(int)(p->position.x)][(int)(p->position.y + p->direction.y * p->speed)] == 0)
				p->position.y += p->direction.y * p->speed;
		}
	if (wolf->flag & 1UL << 1)
		{
			if (map[(int)(p->position.x - p->direction.x * p->speed)][(int)(p->position.y)] == 0)
				p->position.x -= p->direction.x * p->speed;
			if (map[(int)(p->position.x)][(int)(p->position.y - p->direction.y * p->speed)] == 0)
				p->position.y -= p->direction.y * p->speed;
		}
	if (wolf->flag & 1UL << 2)
		{
			if (map[(int)(p->position.x + p->plane.x * p->speed)][(int)(p->position.y)] == 0)
				p->position.x += p->plane.x * p->speed;
			if (map[(int)(p->position.x)][(int)(p->position.y + p->plane.y * p->speed)] == 0)
				p->position.y += p->plane.y * p->speed;
		}
	if (wolf->flag & 1UL << 3)
		{
			if (map[(int)(p->position.x - p->plane.x * p->speed)][(int)(p->position.y)] == 0)
				p->position.x -= p->plane.x * p->speed;
			if (map[(int)(p->position.x)][(int)(p->position.y - p->plane.y * p->speed)] == 0)
				p->position.y -= p->plane.y * p->speed;
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_EQUALS)
	{
		p->direction.x *= 0.9f;
		p->direction.y *= 0.9f;
		p->speed *= 1.1f;
		}
	if (event.key.keysym.scancode == SDL_SCANCODE_MINUS)
	{
		p->direction.x *= 1.1f;
		p->direction.y *= 1.1f;
		p->speed *= 0.9f;
		}
	//printf("plane x\t%f , plane y\t%f\n", p->plane.x, p->plane.y);
	return (1);
}

void	ft_wolf_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
	//SDL_WINDOW_FULLSCREEN
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
	int		j;
	t_wolf	wolf;
	int		fd;
	int frames[120];
	
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
		ft_bzero(frames, sizeof(int) * 120);
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
			my_function(wolf.sdl.event, &wolf, wolf.map);
			//ft_bzero(wolf.img, sizeof(unsigned int) * W * H);
			ceiling(wolf.img);
			render(&wolf);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			if (i == 100)
			{
				i = 1;
				j = 0;
				while (i <= 100)
				{
					printf("%d ms\t", frames[i] - frames[j]);
					i++;
					j++;
				}
				ft_bzero(frames, sizeof(int) * 120);
				printf("\n");
				i = -1;
			}
			i++;
			}
	}
	return (0);
}
