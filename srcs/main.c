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

int		main(int ac, char **av)
{
	t_palette cel;
	t_audio audio;
	t_s32	i;
	t_wolf	wolf;
	t_s32	fd;
	t_s32	frames[61];

	ft_bzero(&audio, sizeof(audio));
	mem_init(&wolf);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("wolf3d.map", O_RDONLY);
	//printf("size of wolf = %ld texture %ld door %ld\n", sizeof(wolf), sizeof(t_texture) , sizeof(t_door));
	//load_music("./music/hallo.wav", &audio);
	//load_music("./music/steps.wav", &audio);
	//SDL_PauseAudio(0);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
		ft_wolf_init(&wolf);
		cel = ceiling();
		count_entities(wolf.map, wolf.obj, wolf.entity);
		init_entities(wolf.entity, &wolf);
		print_map(wolf.map, wolf.obj, wolf.player, wolf.doors, &wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		i = 1;
		ft_bzero(frames, sizeof(t_s32) * 61);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		//SDL_SetWindowFullscreen(wolf.sdl.win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		//printf("tsize = %zu, usize %zu\n", wolf.mem.tsize, wolf.mem.usize);
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
			//TODO (jae) : need a good condition to execute re-order
			sort_depth_buffer(wolf.entity, wolf.entity->item, wolf.player);
			frames[i] = SDL_GetTicks();
			back(&wolf, wolf.img, &cel);
			raycast(&wolf);
			entity_draw_loop(&wolf, wolf.entity, wolf.entity->item, wolf.entity->order);
			if (i == 0)
				draw_hud(&wolf, 16);
			else
				draw_hud(&wolf, frames[i] - frames[i - 1]);
			SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img,
				W * sizeof(t_u32));
			SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
			SDL_RenderPresent(wolf.sdl.renderer);
			ft_frametimes(frames, &i);
			i++;
		}
	}
	return (0);
}
