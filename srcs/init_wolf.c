/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 04:38:32 by viccarau          #+#    #+#             */
/*   Updated: 2019/10/05 23:55:33 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_entities(t_entity *entity, t_wolf *wolf)
{
	t_s32	index;

	is_alloc(entity->item =(t_items*)ft_mem(&wolf->mem,
		sizeof(t_items) * entity->nbr_of_entities), wolf, -1);
	is_alloc(entity->order = (t_s32*)ft_mem(&wolf->mem,
		sizeof(t_s32) * entity->nbr_of_entities), wolf, -1);
	is_alloc(entity->depth = (t_f32*)ft_mem(&wolf->mem,
		sizeof(t_f32) * entity->nbr_of_entities), wolf, -1);
	index = 0;
	while (index < entity->nbr_of_entities)
	{
		entity->item[index].tex = &wolf->tex[12];
		index++;
	}
}

void	ft_wolf_init(t_wolf *wolf, t_sdl *sdl)
{
	wolf->map = int_to_tab(wolf);
	SDL_Init(SDL_INIT_EVERYTHING);
	//sdl->win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
	//SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_FULLSCREEN_DESKTOP);
	sdl->win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
	SDL_SetWindowBordered(sdl->win, SDL_TRUE);
	//printf("wolf->mem.usize = %I64d, %I64d\n", wolf->mem.usize, wolf->mem.tsize);
	//printf("size of img = %I64d\n", W * H * sizeof(t_u32));
	is_alloc(wolf->img = ft_mem(&wolf->mem, W * H * sizeof(t_u32)), wolf, -1);
	is_alloc(wolf->tex = ft_mem(&wolf->mem, sizeof(t_texture) * 20), wolf, -1);
	load_textures(wolf);
	wolf->flag = 0;
	wolf->dist = perp_dist(wolf);
	wolf->a.size = round(W / (1920 / 4));
	wolf->view = 0;
	wolf->a.frame = 100;
	is_alloc(wolf->doors = (t_door*)ft_mem(&wolf->mem, sizeof(t_door) * 100), wolf, -1);
	is_alloc(wolf->player = (t_player*)ft_mem(&wolf->mem, sizeof(t_player)), wolf, -1);
	is_alloc(wolf->player->m = (t_minimap *)ft_mem(&wolf->mem, wolf->obj.size * sizeof(t_minimap)), wolf, -1);
	is_alloc(wolf->perp_dist = (t_f32*)ft_mem(&wolf->mem, sizeof(t_f32) * W), wolf, -1);
	is_alloc(wolf->entity = (t_entity*)ft_mem(&wolf->mem, sizeof(t_entity)), wolf, -1);
	wolf->player->direction.x = 1;
	wolf->player->direction.y = 0;
	wolf->player->plane.x = 0;
	wolf->player->plane.y = 1;
	is_alloc(wolf->p = ft_mem(&wolf->mem, sizeof(t_2d) * wolf->obj.size), wolf, -1);
	init_points(wolf);
}

static t_file	file_str(void)
{
	t_file	file;

	ft_bzero(&file, sizeof(t_file));
	file.str[0] = "./texture/MultibrickD.bmp";
	file.str[1] = "./texture/BookshelfD.bmp";
	file.str[2] = "./texture/WoodbrickD.bmp";
	file.str[3] = "./texture/BrownbrickD.bmp";
	file.str[4] = "./texture/Wooddoor.bmp";
	file.str[5] = "./texture/shotgun0.bmp";
	file.str[6] = "./texture/shotgun1.bmp";
	file.str[7] = "./texture/shotgun2.bmp";
	file.str[8] = "./texture/shotgun3.bmp";
	file.str[9] = "./texture/shotgun4.bmp";
	file.str[10] = "./texture/gun0.bmp";
	file.str[11] = "./texture/gun1.bmp";
	file.str[12] = "./texture/guard0.bmp";
	file.str[13] = "./texture/guard1.bmp";
	return (file);
}

void	load_textures(t_wolf *wolf)
{
	t_s32		i;
	t_palette	pal;
	t_file		file;

	i = -1;
	pal.size = 0;
	file = file_str();
	is_alloc(pal.pal = ft_mem(&wolf->mem, 2948), wolf, 1);
	while (i++ < 13)
		wolf->tex[i] = read_bmp(file.str[i], wolf, &pal);
}
