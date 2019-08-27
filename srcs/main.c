/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */

/*   Updated: 2019/08/25 17:39:31 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		read_all(int fd, uint8_t *data, int size)
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
	uint8_t	data[3 * 64 * 64];
	int		fd;
	uint8_t	header[54];
	t_texture		tex;

	fd = open(filename, O_RDONLY);
	read(fd, header, 54);

	tex.width = TEX_WIDTH;
	tex.height = TEX_HEIGHT;
	tex.size = 3 * tex.width * tex.height;

	int i = 0;
	int j = 0;
	tex.data = (uint32_t*)malloc(tex.width * tex.height * sizeof(uint32_t));
	read_all(fd, data, tex.size);
	i = (64 * 64) - 1;
	while (i >= 0)
	{
		tex.data[i] = data[j] | data[j + 1] << 8 | data[j + 2] << 16;
		i--;
		j += 3;
	}
	return (tex);
}

void	ft_wolf_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
	//SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W * 2, H * 2, 0);
	wolf->img = ft_mem(&wolf->mem, W * H * sizeof(unsigned int));
	wolf->player.direction.x = -1;
	wolf->player.direction.y = 0;
	wolf->player.plane.x = 0;
	wolf->player.plane.y = 1;
	// TODO(viccarau): We will have to make the textures load depending on
	//the type of wall it is. Some textures have to be on the same type of wall.
	wolf->tex[0] = read_bmp("./texture/MultibrickD.bmp");
	wolf->tex[1] = read_bmp("./texture/BrownbrickD.bmp");
	wolf->tex[2] = read_bmp("./texture/BookshelfD.bmp");
	wolf->tex[3] = read_bmp("./texture/WoodbrickD.bmp");
	wolf->tex[4] = read_bmp("./texture/Wooddoor.bmp");
	wolf->player.speed = 0;
	wolf->flag = 0;
}

void	ceiling(unsigned int *img)
{
	int x;
	int y;
	int y1;
	int color;
	float per;

	x = 0;
	y = 0;
	y1 = H;
	per = 2.71f;
	while (y < H / 2)
	{
		x = 0;
		color = rgb_lerp(0x111111, per, 0x222222);
		while (x < W)
		{
			img[x + y * W] = color;
			img[x + y1 * W] = 0x222222 + color;
			x++;
		}
		per -= 0.01f;
		y++;
		y1--;
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
		print_map(wolf.map, wolf.obj, &wolf.player, wolf.doors, &wolf);
		ft_wolf_init(&wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		i = 1;
		ft_bzero(frames, sizeof(int) * 61);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		while (1)
		{
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					is_alloc(NULL, wolf, 0);
				set_flag(&wolf, wolf.sdl.event);
				if (wolf.sdl.event.type == SDL_KEYDOWN)
					event_handler(&wolf, wolf.map, wolf.doors);
			}
			if (i != 0)
				direction_movement(&wolf, wolf.map,
					SDL_GetTicks() - frames[i - 1]);
			frames[i] = SDL_GetTicks();
			//ft_bzero(wolf.img, sizeof(unsigned int) * W * H);
			ceiling(wolf.img);
			//render(&wolf);
			raycast(&wolf);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img,
				W * sizeof(unsigned int));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			ft_frametimes(frames, &i);
			i++;
		}
	}
	return (0);
}
