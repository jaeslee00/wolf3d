/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/24 13:43:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_m3x3	final_projection(t_wolf *wolf)
{
	t_m3x3	r;

	r = identity();
	r = mx_mul(scale(wolf->player->m->scale), mx_mul(rot(wolf->player->m->rotation), identity()));
	return (r);
}

static void	general_inits(t_wolf *wolf, t_s32 fd, t_2d_p *time, t_sdl *sdl)
{
	ft_bzero(time, sizeof(t_2d_p));
	tkneizer(fd, wolf);
	ft_wolf_init(wolf, sdl);
	wolf->proj_matrix = identity();
	wolf->player->m->rotation = 90.f * PI32 / 180.f;
	wolf->player->m->scale = 15;
	wolf->proj_matrix = final_projection(wolf);
	count_entities(wolf->map, wolf->obj, wolf->entity);
	init_entities(wolf->entity, wolf);
	print_map(wolf->map, wolf->obj, wolf->player, wolf->doors, wolf);
	sdl->renderer = SDL_CreateRenderer(sdl->win, -1, 0);
	sdl->texture = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

static void	get_input(t_wolf *wolf, t_s32 deltatime, t_sdl *sdl)
{
	while (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.type == SDL_QUIT)
			exit(0);
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			is_alloc(NULL, wolf, 0);
		set_flag(wolf, sdl->event);
		mouse_movement(wolf, sdl->event);
	}
	check_flag(wolf, wolf->map, deltatime);
}

static void	draw_on_screen(t_wolf *wolf, t_s32 deltatime, t_sdl *sdl)
{
	entity_draw_loop(wolf, wolf->entity->item, wolf->entity->order, wolf->entity->nbr_of_entities);
	wolf->proj_matrix = final_projection(wolf);
	draw_hud(wolf, deltatime);
	SDL_UpdateTexture(sdl->texture, NULL, wolf->img,
		W * sizeof(t_u32));
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}

int		main(int ac, char **av)
{
	t_sdl		sdl;
	t_wolf		wolf;
	t_s32		fd;
	t_2d_p		time;
	
	fd = mem_init(&wolf, ac, av);
	if (fd > 0)
	{
		general_inits(&wolf, fd, &time, &sdl);
		while (1)
		{
			time.x = SDL_GetTicks();
			get_input(&wolf, time.x - time.y, &sdl);
			printf("%d ms\t", time.x - time.y);
			time.y = SDL_GetTicks();
			event_handler(&wolf, wolf.map, wolf.doors);
			sort_depth_buffer(wolf.entity, wolf.entity->item, wolf.player);
			background(&wolf, wolf.img);
			raycast(&wolf);
			draw_on_screen(&wolf, SDL_GetTicks() - time.x, &sdl);
		}
	}
	return (0);
}
