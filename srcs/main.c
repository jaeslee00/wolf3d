/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/28 12:33:58 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_wolf_init(t_wolf *wolf)
{
	wolf->map = int_to_tab(wolf);
	SDL_Init(SDL_INIT_EVERYTHING);
	//wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
	//SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W * 2, H * 2, 0);
	wolf->img = ft_mem(&wolf->mem, W * H * sizeof(uint32));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("%s\n", Mix_GetError());
		exit(0);
	}
	if (!(wolf->sdl.music = Mix_LoadMUS("music/hallo.wav")))
	{
		printf("%s\n", Mix_GetError());
		exit(0);
	}
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
		if (color == 0)
			color = 0;
else
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
		ft_wolf_init(&wolf);
		print_map(wolf.map, wolf.obj, &wolf.player, wolf.doors, &wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		i = 1;
		ft_bzero(frames, sizeof(sint32) * 61);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		Mix_PlayMusic(wolf.sdl.music, -1);
		while (1)
		{
			//printf("wolf %ld\n", wolf.mem.usize);
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					is_alloc(NULL, wolf, 0);
				set_flag(&wolf, wolf.sdl.event);
				mouse_movement(&wolf, wolf.sdl.event);
				}
			if (i != 0)
				check_flag(&wolf, wolf.map,
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
