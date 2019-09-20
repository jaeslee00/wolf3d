/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/09 18:20:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	general_inits(t_wolf *wolf, t_s32 fd, t_2d_p *time)
{
	ft_bzero(time, sizeof(t_2d_p));
	tkneizer(fd, wolf);
	ft_wolf_init(wolf);
	count_entities(wolf->map, wolf->obj, wolf->entity);
	init_entities(wolf->entity, wolf);
	print_map(wolf->map, wolf->obj, wolf->player, wolf->doors, wolf);
	wolf->sdl.renderer = SDL_CreateRenderer(wolf->sdl.win, -1, 0);
	wolf->sdl.texture = SDL_CreateTexture(wolf->sdl.renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

static void	get_input(t_wolf *wolf, t_s32 deltatime)
{
	while (SDL_PollEvent(&wolf->sdl.event))
	{
		if (wolf->sdl.event.type == SDL_QUIT)
			exit(0);
		if (wolf->sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			is_alloc(NULL, wolf, 0);
		set_flag(wolf, wolf->sdl.event);
		mouse_movement(wolf, wolf->sdl.event);
	}
	check_flag(wolf, wolf->map, deltatime);
}


static void	draw_on_screen(t_wolf *wolf, t_s32 deltatime)
{
	entity_draw_loop(wolf, wolf->entity, wolf->entity->item, wolf->entity->order);
	draw_hud(wolf, deltatime);
	SDL_UpdateTexture(wolf->sdl.texture, NULL, wolf->img,
		W * sizeof(t_u32));
	SDL_RenderCopy(wolf->sdl.renderer, wolf->sdl.texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.renderer);
}

int		main(int ac, char **av)
{
	t_wolf		wolf;
	t_s32		fd;
	t_2d_p		time;
	
	fd = mem_init(&wolf, ac, av);
	if (fd > 0)
	{
		general_inits(&wolf, fd, &time);
		while (1)
		{
			time.x = SDL_GetTicks();
			get_input(&wolf, time.x - time.y);
			time.y = SDL_GetTicks();
			event_handler(&wolf, wolf.map, wolf.doors);
			sort_depth_buffer(wolf.entity, wolf.entity->item, wolf.player);
			background(&wolf, wolf.img);
			raycast(&wolf);
			draw_on_screen(&wolf, SDL_GetTicks() - time.x);
		}
	}
	return (0);
}
