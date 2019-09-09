/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:51:29 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/09 20:28:55 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	my_audio_callback(void *userdata, Uint8 *stream, int len)
{
	t_audio *a;

	a = (t_audio *)userdata;
	if (a->audio_len == 0)
		return;
len = (len > (int)a->audio_len ? (int)a->audio_len : len);
ft_memcpy(stream, a->audio_pos, len);
	a->audio_pos += len;
	a->audio_len -= len;
}

void	load_music(char *path, t_audio *audio)
{
	if (SDL_LoadWAV(path, &audio->wav_spec,
			&audio->wav_buffer, &audio->wav_length) == NULL )
		exit(0);
	audio->wav_spec.callback = my_audio_callback;
	audio->wav_spec.userdata = audio;
	audio->audio_pos = audio->wav_buffer;
	audio->audio_len = audio->wav_length;
	SDL_OpenAudio(&audio->wav_spec, NULL);
	//exit(-1);
	}
