/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/04 12:11:43 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_textures(t_wolf *wolf)
{
	wolf->tex[0] = read_bmp("./texture/MultibrickD.bmp", wolf);
	wolf->tex[1] = read_bmp("./texture/BookshelfD.bmp", wolf);
	wolf->tex[2] = read_bmp("./texture/BrownbrickD.bmp", wolf);
	wolf->tex[3] = read_bmp("./texture/WoodbrickD.bmp", wolf);
	wolf->tex[4] = read_bmp("./texture/Wooddoor.bmp", wolf);
	wolf->tex[5] = read_bmp("./texture/shotgun0.bmp", wolf);
	wolf->tex[6] = read_bmp("./texture/shotgun1.bmp", wolf);
	wolf->tex[7] = read_bmp("./texture/shotgun2.bmp", wolf);
	wolf->tex[8] = read_bmp("./texture/shotgun3.bmp", wolf);
	wolf->tex[9] = read_bmp("./texture/shotgun4.bmp", wolf);
	wolf->tex[10] = read_bmp("./texture/gun0.bmp", wolf);
	wolf->tex[11] = read_bmp("./texture/gun1.bmp", wolf);
	wolf->npc[0].tex[0] = read_bmp("./texture/guard/guard00.bmp", wolf);
	wolf->npc[1].tex[0] = read_bmp("./texture/guard/guard00.bmp", wolf);
	wolf->npc[2].tex[0] = read_bmp("./texture/guard/guard00.bmp", wolf);
	wolf->npc[3].tex[0] = read_bmp("./texture/guard/guard00.bmp", wolf);
	wolf->npc[4].tex[0] = read_bmp("./texture/guard/guard00.bmp", wolf);
}

void	ft_wolf_init(t_wolf *wolf)
{
	wolf->map = int_to_tab(wolf);
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
	SDL_SetWindowBordered(wolf->sdl.win, SDL_TRUE);
	wolf->img = ft_mem(&wolf->mem, W * H * sizeof(uint32));
	wolf->player.direction.x = -1;
	wolf->player.direction.y = 0;
	wolf->player.plane.x = 0;
	wolf->player.plane.y = 1;
	is_alloc(wolf->tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	is_alloc(wolf->npc[0].tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	is_alloc(wolf->npc[1].tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	is_alloc(wolf->npc[2].tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	is_alloc(wolf->npc[3].tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	is_alloc(wolf->npc[4].tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	load_textures(wolf);
	wolf->player.speed = 0;
	wolf->flag = 0;
	wolf->dist = perp_dist(wolf);
	wolf->player.health = 75;
	wolf->a.size = round(W / (1920 / 4));
	wolf->map_width = wolf->obj.len;
	wolf->map_height = wolf->obj.size / wolf->obj.len;
	wolf->player.minimap_width = wolf->map_width + 1;
	wolf->player.minimap_height = wolf->map_height + 1;
	wolf->player.minimap_zoom = 20;
	wolf->view = 0;
	wolf->a.frame = 100;
	wolf->npc[0].pos.x = 8.0f;
	wolf->npc[0].pos.y = 3.0f;
	wolf->npc[1].pos.x = 6.0f;
	wolf->npc[1].pos.y = 1.5f;
	wolf->npc[2].pos.x = 13.0f;
	wolf->npc[2].pos.y = 7.0f;
	wolf->npc[3].pos.x = 6.5f;
	wolf->npc[3].pos.y = 8.5f;
	wolf->npc[4].pos.x = 9.5f;
	wolf->npc[4].pos.y = 2.5f;
	is_alloc(wolf->doors = ft_mem(&wolf->mem, sizeof(t_door) * 100), wolf, -1);
	is_alloc(wolf->player.m = (t_minimap *)ft_mem(&wolf->mem, (wolf->obj.size / wolf->obj.len) * (wolf->obj.len) * sizeof(t_minimap)), wolf, -1);
}

void	*test(void *b, int c, size_t len)
{
	uint32	*a1;
	uint8		*a2;

	a1 = (uint32 *)b;
	while (len - 4 > 0)
	{
		*a1++ = c;
		len -= 4;
	}
	a2 = (uint8 *)b;
	while (len--)
		*a2++ = c;
	return (b);
}

void	ceiling(uint32 *img, t_wolf *wolf)
{
	sint32	x;
	sint32	y;
	sint32	y1;
	sint32	color;
	f32		per;

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
}

int		main(int ac, char **av)
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
	//printf("size of wolf = %ld texture %ld door %ld\n", sizeof(wolf), sizeof(t_texture) , sizeof(t_door));
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
		SDL_SetWindowFullscreen(wolf.sdl.win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		while (1)
		{
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					is_alloc(NULL, &wolf, 0);
				set_flag(&wolf, wolf.sdl.event);
				mouse_movement(&wolf, wolf.sdl.event);
			}
			//ft_memset(img, 0, W * H * 4);
			if (i != 0)
				check_flag(&wolf, wolf.map,
					SDL_GetTicks() - frames[i - 1]);
			event_handler(&wolf, wolf.map, wolf.doors);
			frames[i] = SDL_GetTicks();
			ceiling(wolf.img, &wolf);
			raycast(&wolf);
			move_npc(&wolf.npc[0]);
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
