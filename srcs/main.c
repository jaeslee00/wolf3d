/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
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

void	init_precalc(t_precalc *calc)
{
	int i;

	i = 0;
	while (i < 360)
	{
		calc->sins[i] = my_sin(degree_radian(i));
		calc->asins[i] = my_asin(degree_radian(i));
		calc->cosins[i] = my_cos(degree_radian(i));
		calc->acosins[i] = my_acos(degree_radian(i));
		calc->tan[i] = my_tan(degree_radian(i));
		calc->atan[i] = my_atan(degree_radian(i));
		i++;
	}
	}

int		my_function(int keycode, t_wolf *wolf)
{
	if (keycode == SDL_SCANCODE_R)
		printf("\nYou pressed R\n\n");
	if (keycode == SDL_SCANCODE_ESCAPE)
		is_alloc(NULL, *wolf, 0);
	return (1);
}

void	calculate_distance(t_player *p, t_2d_p *a)
{
p->ray.y = (p->position.y >> 8) * (64) - 1;
	p->ray.x = (p->position.x) + (p->position.y - p->ray.y) / my_tan(FOV);
	a->y = -64;
	a->x = 64 / my_tan(FOV);
}

void	ft_raycast(t_wolf *wolf, t_player *player)
{
	t_2d_p a;
	t_2d_p *ray;
	int x;
	int y;
	int hit;
	int **map;
	
	map = int_to_tab(wolf->obj);
	calculate_distance(player, &a);
	ray = &player->ray;
	hit = 0;
while (!hit)
	{
		 x = (ray->x + a.x);
		y = (ray->y + a.y);
		if (map[ray->y >> 8][ray->x >> 8] == 64)
			hit = 1;
	}
}

void	ft_wolf_init(t_wolf *wolf, t_player *p)
{
	t_precalc c;

	init_precalc(&c);
	printf("sin(30) = %f %f\n", c.sins[30], c.cosins[30]);
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
	wolf->img = ft_memalloc(W * H * sizeof(unsigned int));
	p->arc = W / 12;
	p->distance = 426;
	p->height = 32;
	p->speed = 16;
}

int		main(int ac, char **av)
{
	int		i;
	t_wolf	wolf;
	t_player p;
	int		fd;
	
	//float	avg_fps;
	
	p.direction.x = 0;
	p.direction.y = -1.0f;
	//p.plane.x = 0;
	//p.plane.y = 80;

	/*
 center of projection plane = (640, 360);
 distance to the projection plane = 426;
 angle between rays = FOV / 1280;
 */

	mem_init(&wolf);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("test.map", O_RDONLY);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
		print_map(int_to_tab(wolf.obj), wolf.obj, &p);
		printf("\nplayer = %d, %d\n", p.position.x, p.position.y);
		ft_wolf_init(&wolf, &p);
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
			}
			//if (i % 100 == 0)
			//printf("fps = %f\n", avg_fps);
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
