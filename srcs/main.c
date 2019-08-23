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

int		read_all(int fd, unsigned char *data, int size)
{
	int	read_bytes;
	int	ret;

	read_bytes = 0;
	while (((ret = read(fd, data + read_bytes, size - read_bytes)) > 0))
		read_bytes = read_bytes + ret;
	if (ret <= 0)
		return (ret);
	return (read_bytes + ret);
}

t_texture	read_bmp(const char *filename)
{
	unsigned char *data;
	int fd;
	unsigned char header[54];
	t_texture		tex;

	fd = open(filename, O_RDONLY);
	read(fd, header, 54);

	tex.width = TEX_WIDTH;
	tex.height = TEX_HEIGHT;
	tex.size = 3 * tex.width * tex.height;

	int i = 0;
	int j = 0;
	data = (unsigned char*)malloc(tex.size);
	tex.data = (unsigned int*)malloc(tex.width * tex.height * sizeof(int));
	read_all(fd, data, tex.size);
	i = (64 * 64) - 1;
	while (i >= 0)
	{
		tex.data[i] = data[j] | data[j + 1] << 8 | data[j + 2] << 16;
		i--;
		j += 3;
	}
	free(data);
	return (tex);
}

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
	wolf->tex[0] = read_bmp("./texture/eagle.bmp");
	wolf->tex[1] = read_bmp("./texture/colorstone.bmp");
	wolf->tex[2] = read_bmp("./texture/greystone.bmp");
	wolf->tex[3] = read_bmp("./texture/redbrick.bmp");
	wolf->player.speed = 0.05f;
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

void img_to_screen(unsigned int *img, t_texture t)
{
	int x;
	int y;

	x = 0;
	while (x < t.width)
	{
		y = 0;
		while (y < t.height)
		{
			img[x + y * W] = t.data[x + y * W];
			y++;
		}
		x++;
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
		fd = open("wolf3d.map", O_RDONLY);
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
			//render(&wolf);
			raycast(&wolf);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			ft_frametimes(frames, &i);
			i++;
		}
	}
	return (0);
}
