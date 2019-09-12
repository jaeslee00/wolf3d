/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/09 18:19:44 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TODO(viccarau): For optimisation purposes we need to make the size of the
   **				 structs64-bytes maximum. That is the cache-line size on the
**				processor we're working on.
**				I think we should allocate all the structs inside our wolf.
** TODO(viccarau): protect the textures SHERLOCK
*/

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "draw.h"
# include <math.h>
# include <SDL2/SDL.h>
// # define W	(2560)
// # define H	(1080)
# define W	(3840)
# define H	(2160)

# define TEXTURE_0	0
# define TEXTURE_1	1
# define TEXTURE_2	2
# define TEXTURE_3	3
# define TEXTURE_4	4

# define OBJ_ON_TARGET 1UL
# define OBJ_DAMAGED 1UL << 1
# define OBJ_DEAD 1UL << 2

# define ENEMY_SIZE 50
# define NBR_OF_ENTITIES 9
# define TEXTURE_BLANK 0x980088
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif
# ifndef PI32
#  define PI32 3.14159265359f
# endif

//
#include <stdio.h>

typedef unsigned char		uint8;
typedef char				sint8;

typedef unsigned short int	uint16;
typedef short int			sint16;

typedef unsigned int		uint32;
typedef int					sint32;

typedef unsigned long long int	uint64;
typedef long long int			sint64;

typedef float				f32;
typedef double				f64;

/*
** E[ROW][COLUMN]
** ROW Major
*/

typedef struct	s_2d_p
{
	sint32	x;
	sint32	y;
}				t_2d_p;

typedef struct	s_audio
{
	SDL_AudioSpec	wav_spec;
	uint8	*wav_buffer;
	uint32	wav_length;
	uint8	*audio_pos;
	uint32	audio_len;

}				t_audio;

typedef struct	s_texture
{
	sint32			width;
	sint32			height;
	sint32			size;
	uint32_t		*data;
}				t_texture;

typedef struct	s_texture_map
{
	sint32	start;
	sint32	end;
	t_2d_p	coord;
	sint32	column_height;
}				t_texture_map;

typedef struct	s_door
{
	uint64	state;
	t_2d_p	pos;
	uint8	flag;
}				t_door;

typedef struct	s_minimap
{
	sint32	x;
	sint32	y;
	sint32	h_color_head;
	sint32	h_color_tail;
	sint32	v_color_head;
	sint32	v_color_tail;
}				t_minimap;

typedef struct	s_obj
{
sint8	*nb;
	sint32	size;
	sint32	w;
	sint32	h;
}				t_obj;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Texture		*texture;
}				t_sdl;

typedef struct	s_palette
{
	uint32	*palete;
	uint32		size;
	}				t_palette;

typedef struct	s_player
{
	t_2d		ray;
	t_2d		pos;
	t_2d		direction;
	t_2d		plane;
	f32			speed;
	//TODO (jae) : maybe it's better to put t_minimap + minimap infos into another structure heheh
	
	t_minimap	*m;
	sint32		minimap_zoom;
	int			health;
}				t_player;

typedef struct	s_animation
{
	sint32	gun;
	uint32	frame;
	uint32	size;
}				t_animation;

typedef struct	s_raycaster
{
	t_2d_p	step;
	t_2d_p	map;
	t_2d	side_dist;
	t_2d	delta_dist;
	t_2d	plane;
	f32		perp_dist;
	//id_t	tex_flag;
	sint32	hit;
	sint32	side;
}				t_raycaster;

typedef f32 (*funct)(t_raycaster * ray, t_player *player);

//TODO (jae) : need to have multiple textures for status of NPC
typedef struct	s_items
{
	sint32		id;
	t_2d		pos;
	t_2d		transformed_sprite_pos;
	sint32		flag;
	sint32		hp;
	t_texture	*tex;
}				t_items;

typedef struct	s_entity
{
	sint32	nbr_of_entities;
	f32		*depth;
	sint32	*order;
	t_items	*item;
}				t_entity;


typedef struct	s_wolf
{
	funct		*dist;
	t_player	*player;
	t_sdl		sdl;
	t_obj		obj;
	uint32		*img;
	t_mem		mem;
	sint8		**map;
	t_door		*doors;
	uint32		nbr_of_doors;
	uint32		door_idx;
	t_texture	*tex;
	uint32		flag;
	uint8		res;
	t_animation	a;
	sint32		view;
	t_entity	*entity;
	f32			*perp_dist;
}				t_wolf;

void				load_music(char *path, t_audio *audio);
void				draw_hud(t_wolf *wolf, uint32 deltaframe);
t_2d_p			init_2d(sint32 x, sint32 y);
void				draw_sprite(t_wolf *wolf, t_2d_p start, t_texture tex, uint32 size);
funct			*perp_dist(t_wolf *wolf);
f32				perp_distance_ew(t_raycaster *ray, t_player *player);
f32				perp_distance_sn(t_raycaster *ray, t_player *player);
f32				perp_distance_ew_door(t_raycaster *ray, t_player *player);
f32				perp_distance_sn_door(t_raycaster *ray, t_player *player);
f32				my_sin(f32 angle);
f32				my_cos(f32 angle);
f32				my_asin(f32 angle);
f32				my_acos(f32 angle);
f32				my_tan(f32 angle);
f32				my_atan(f32 angle);
f32				degree_radian(sint32 degree);
f64				fov_calculator(t_wolf *wolf);
f64				ft_abs(f64 x);
sint8			**int_to_tab(t_wolf *wolf);
sint32			is_invalid(char *str);
sint32			is_valid(f32 x, f32 y);
sint32			tkneizer(sint32 fd, t_wolf *wolf);
sint32			lerp(f64 a, f32 t, f64 b);
sint32			rgb_lerp(sint32 color1, f32 t, sint32 color2);
sint32			direction_movement(t_wolf *wolf, sint8 **map, sint32 framedelta);
sint32			print_map(char **map, t_obj obj, t_player *player, t_door *doors, t_wolf *wolf);
void			palette(uint32 *img, t_palette *p, uint32 size);
void			check_flag(t_wolf *wolf, sint8 **map, sint32 framedelta);
void			set_flag(t_wolf *wolf, SDL_Event event);
void			ft_frametimes(sint32 *frames, sint32 *count);
void			event_handler(t_wolf *wolf, char **map, t_door *doors);
void			render(t_wolf *wolf);
void			raycast(t_wolf *wf);
void			calculate_distance(t_player *p, t_2d_p *a);
void			ft_raycast(t_wolf *wolf, t_player *player);
void			draw_minimap(t_wolf *wolf);
void			mem_init(t_wolf *wolf);
void			is_alloc(void *mem, t_wolf *wolf, sint32 error);
void			draw_to_img(t_wolf wolf);
void			pers_keys(sint32 keycode, t_wolf *wolf);
void			minimap(t_wolf *wolf);
void			mouse_movement(t_wolf *wolf, SDL_Event event);
void			draw_gun(t_wolf *wolf, uint32 tex_id);
void			draw_machinegun(t_wolf *wolf, uint32 deltaframe);
void			draw_wall(t_wolf *wf, sint32 line_height, sint32 x, t_raycaster *ray);
sint32			lighting(sint32 color, f32 distance);
t_texture		read_bmp(const sint8 *filename, t_wolf *wolf, t_palette *pal);
void			entity_update(t_wolf *wf);
void			entity_draw(t_items *item, t_texture *tex, sint32 view, uint32 *img, f32 *perp_dist);
void			entity_draw_loop(t_wolf *wf, t_entity *entity, t_items *item, sint32 *order);
void			sort_depth_buffer(t_entity *entity, t_items *item, t_player *player);
void			count_entities(sint8 **map, t_obj obj, t_entity *entity);
#endif
