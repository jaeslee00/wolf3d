/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/09 20:29:24 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_textures(t_wolf *wolf)
{
t_palette pal;

	pal.size = 0;
	is_alloc(pal.palete = ft_mem(&wolf->mem, 2948), wolf, -1);
	wolf->tex[0] = read_bmp("./texture/MultibrickD.bmp", wolf, &pal);
	wolf->tex[1] = read_bmp("./texture/BookshelfD.bmp", wolf, &pal);
	wolf->tex[2] = read_bmp("./texture/BrownbrickD.bmp", wolf, &pal);
	wolf->tex[3] = read_bmp("./texture/WoodbrickD.bmp", wolf, &pal);
	wolf->tex[4] = read_bmp("./texture/Wooddoor.bmp", wolf, &pal);
	wolf->tex[5] = read_bmp("./texture/shotgun0.bmp", wolf, &pal);
	wolf->tex[6] = read_bmp("./texture/shotgun1.bmp", wolf, &pal);
	wolf->tex[7] = read_bmp("./texture/shotgun2.bmp", wolf, &pal);
	wolf->tex[8] = read_bmp("./texture/shotgun3.bmp", wolf, &pal);
	wolf->tex[9] = read_bmp("./texture/shotgun4.bmp", wolf, &pal);
	wolf->tex[10] = read_bmp("./texture/gun0.bmp", wolf, &pal);
	wolf->tex[11] = read_bmp("./texture/gun1.bmp", wolf, &pal);
	wolf->tex[12] = read_bmp("./texture/guard/guard00.bmp", wolf, &pal);
	wolf->tex[13] = read_bmp("./texture/guard/guard01.bmp", wolf, &pal);
	//printf("pal size = %I64d, \n", pal.size * sizeof(int));
}

void	ft_wolf_init(t_wolf *wolf)
{
	wolf->map = int_to_tab(wolf);
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
	SDL_SetWindowBordered(wolf->sdl.win, SDL_TRUE);
	wolf->img = ft_mem(&wolf->mem, W * H * sizeof(uint32));
	is_alloc(wolf->tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	load_textures(wolf);
	wolf->flag = 0;
	wolf->dist = perp_dist(wolf);
	wolf->a.size = round(W / (1920 / 4));
	wolf->map_width = wolf->obj.len;
	wolf->map_height = wolf->obj.size / wolf->obj.len;
	wolf->view = 0;
	wolf->a.frame = 100;
	is_alloc(wolf->doors = (t_door*)ft_mem(&wolf->mem, sizeof(t_door) * 100), wolf, -1);
	is_alloc(wolf->player = (t_player*)ft_mem(&wolf->mem, sizeof(t_player)), wolf, -1);
	is_alloc(wolf->player->m = (t_minimap *)ft_mem(&wolf->mem, wolf->obj.size * sizeof(t_minimap)), wolf, -1);
	is_alloc(wolf->perp_dist = (f32*)ft_mem(&wolf->mem, sizeof(f32) * W), wolf, -1);
	is_alloc(wolf->entity = (t_entity *)ft_mem(&wolf->mem, sizeof(t_entity) * NBR_OF_ENTITIES), wolf, -1);
wolf->player->direction.x = -1;
	wolf->player->direction.y = 0;
	wolf->player->plane.x = 0;
	wolf->player->plane.y = 1;
	wolf->player->speed = 0;
	wolf->player->health = 75;
	wolf->player->minimap_width = wolf->map_width + 1;
	wolf->player->minimap_height = wolf->map_height + 1;
	wolf->player->minimap_zoom = 20;
}

void back(uint32 *img, t_palette *cel)
{
	sint32	x;
	sint32	y;
	sint32	y1;
	sint32	i;

	i = 0;
	y = 0;
	y1 = H - 1;
	while (y < (H / 2))
	{
		x = 0;
		while (x < W - 1)
		{
			if (i < (int)cel->size)
{
				img[x + y * W] = cel->palete[i];
				img[x + y1 * W] = cel->palete[i];
			}
else
			{
				img[x + y * W] = 0;
				img[x + y1 * W] = 0;
			}
			x++;
		}
		if (y % 20 == 0)
			i++;
		y++;
		y1--;
	}
}

	t_palette ceiling(uint32 *img, t_wolf *wolf)
{
	t_palette p;
	sint32	x;
	sint32	y;
	sint32	y1;
	sint32	color;
	f32		per;

	ft_bzero(&p, sizeof(p));
	p.palete = ft_memalloc(sizeof(sint32) * 20000);
	color = 1;
	x = 0;
	y = 0;
	y1 = H - 1;
	per = 2.71f;
	while (y < (H / 2) - wolf->view)
	{
		x = 0;
		if (color == 0)
			color = 0;
		else
			color = rgb_lerp(0x111111, per, 0x222222);
		while (x < W - 1)
		{
			img[x + y * W] = color;
			x++;
		}
		per -= 0.01f;
		y++;
	}
	y = 0;
	while (y < (H / 2) + wolf->view)
	{
		x = 0;
		if (color == 0)
			color = 0;
		else
			color = rgb_lerp(0x111111, per, 0x222222);
		while (x < W - 1)
		{
			img[x + y1 * W] = 0x333333 + color;
			x++;
		}
		per -= 0.01f;
		y++;
		y1--;
	}
	palette(img, &p, W * H * 2);
	//printf("sizeof(pal) = %d\n", p.size);
	return (p);
}

int		main(int ac, char **av)
{
	t_palette cel;
	t_audio audio;
	sint32	i;
	t_wolf	wolf;
	sint32	fd;
	sint32	frames[61];
	
	ft_bzero(&audio, sizeof(audio));
mem_init(&wolf);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("wolf3d.map", O_RDONLY);
	//printf("size of wolf = %ld texture %ld door %ld\n", sizeof(wolf), sizeof(t_texture) , sizeof(t_door));
	load_music("./music/hallo.wav", &audio);
	//load_music("./music/steps.wav", &audio);
	//SDL_PauseAudio(0);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
		ft_wolf_init(&wolf);
		cel = ceiling(wolf.img, &wolf);
		print_map(wolf.map, wolf.obj, wolf.player, wolf.doors, &wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		i = 1;
		ft_bzero(frames, sizeof(sint32) * 61);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_SetWindowFullscreen(wolf.sdl.win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		printf("tsize = %I64d, usize %I64d\n", wolf.mem.tsize, wolf.mem.usize);
		while (1)
		{
if (audio.audio_len == 0)
			{
				audio.audio_pos = audio.wav_buffer;
				audio.audio_len = audio.wav_length;
			}
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					is_alloc(NULL, &wolf, 0);
				set_flag(&wolf, wolf.sdl.event);
				mouse_movement(&wolf, wolf.sdl.event);
			}
			if (i != 0)
				check_flag(&wolf, wolf.map,
					SDL_GetTicks() - frames[i - 1]);
			event_handler(&wolf, wolf.map, wolf.doors);
			frames[i] = SDL_GetTicks();
			back(wolf.img, &cel);
			raycast(&wolf);
			entity_update(&wolf);
			if (i == 0)
				draw_hud(&wolf, 16);
			else
				draw_hud(&wolf, frames[i] - frames[i - 1]);
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
