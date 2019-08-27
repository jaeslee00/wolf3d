/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/27 13:49:33 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

sint32	read_all(sint32 fd, uint8 *data, sint32 size)
{
	sint32	read_bytes;
	sint32	ret;

	read_bytes = 0;
	while (((ret = read(fd, data + read_bytes, size - read_bytes)) > 0))
		read_bytes = read_bytes + ret;
	if (ret <= 0)
		return (ret);
	return (read_bytes + ret);
}

t_texture	read_bmp(const sint8 *filename)
{
	uint8	data[3 * 64 * 64];
	sint32	fd;
	uint8	header[54];
	t_texture		tex;

	fd = open(filename, O_RDONLY);
	read(fd, header, 54);

	tex.width = TEX_WIDTH;
	tex.height = TEX_HEIGHT;
	tex.size = 3 * tex.width * tex.height;

	sint32 i = 0;
	sint32 j = 0;
	tex.data = (uint32*)malloc(tex.width * tex.height * sizeof(uint32));
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
	wolf->img = ft_mem(&wolf->mem, W * H * sizeof(uint32));
	wolf->player.direction.x = -1;
	wolf->player.direction.y = 0;
	wolf->player.plane.x = 0;
	wolf->player.plane.y = 1;
	wolf->tex[0] = read_bmp("./texture/MultibrickD.bmp");
	wolf->tex[1] = read_bmp("./texture/BookshelfD.bmp");
	wolf->tex[2] = read_bmp("./texture/BrownbrickD.bmp");
	wolf->tex[3] = read_bmp("./texture/WoodbrickD.bmp");
	wolf->tex[4] = read_bmp("./texture/Wooddoor.bmp");
	wolf->player.speed = 0;
	wolf->flag = 0;
}

void	ceiling(uint32 *img)
{
	sint32 x;
	sint32 y;
	sint32 y1;
	sint32 color;
	f32 per;

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

void img_to_screen(uint32 *img, t_texture t)
{
	sint32	x;
	sint32	y;

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

int	main(int ac, char **av)
{
	sint32	i;
	t_wolf	wolf;
	sint32	fd;
		sint32	frames[61];

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
		ft_bzero(frames, sizeof(sint32) * 61);
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
				}
			if (i != 0)
				direction_movement(&wolf, wolf.map,
					SDL_GetTicks() - frames[i - 1]);
			event_handler(&wolf, wolf.map, wolf.doors);
			frames[i] = SDL_GetTicks();
			//ft_bzero(wolf.img, sizeof(uint32) * W * H);
			ceiling(wolf.img);
			//render(&wolf);
			raycast(&wolf);
			if (wolf.flag & 1UL << 8)
				minimap(&wolf);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img,
				W * sizeof(uint32));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			ft_frametimes(frames, &i);
			i++;
		}
	}
	return (0);
}
