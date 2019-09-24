/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/24 12:57:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "draw.h"
# include <math.h>
# include <SDL2/SDL.h>
// # define W	(2560)
//# define H	(1440)
//#define W	(720)
//#define H	(520)
 //# define W	(3120)
 //# define H	(2080)
 # define W	(1920)
 # define H	(1080)
# define TEXTURE_0	0
# define TEXTURE_1	1
# define TEXTURE_2	2
# define TEXTURE_3	3
# define TEXTURE_4	4

# define OBJ_ON_TARGET 1UL
# define OBJ_DAMAGED 1UL << 1
# define OBJ_DEAD 1UL << 2

# define ENEMY_SIZE 50
# define NBR_OF_ENTITIES 10
# define TEXTURE_BLANK 0x980088
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif
# ifndef PI32
#  define PI32 3.14159265359f
# endif

//
#include <stdio.h>

typedef unsigned char		t_u8;
typedef char				t_s8;

typedef unsigned short int	t_u16;
typedef short int			t_s16;

typedef unsigned int		t_u32;
typedef int					t_s32;

typedef unsigned long long int	t_u64;
typedef long long int			t_s64;

typedef float				t_f32;
typedef double				t_f64;

/*
** E[ROW][COLUMN]
** ROW Major
*/

typedef struct	s_2d_p
{
	t_s32	x;
	t_s32	y;
}				t_2d_p;

typedef enum e_raycast_obj
{
	e_ew_wall,
	e_sn_wall,
	e_sn_door,
	e_ew_door
}			t_raycast_obj;

typedef struct	s_audio
{
	SDL_AudioSpec	wav_spec;
	t_u8			*wav_buffer;
	t_u32			wav_length;
	t_u8			*audio_pos;
	t_u32			audio_len;
}				t_audio;

typedef struct	s_texture
{
	t_s32			width;
	t_s32			height;
	t_s32			size;
	t_u32			*data;
}				t_texture;

typedef struct	s_texture_map
{
	t_s32	start;
	t_s32	end;
	t_2d_p	coord;
	t_s32	column_height;
}				t_texture_map;

typedef struct	s_door
{
	t_u64	state;
	t_2d_p	pos;
	t_u8	flag;
}				t_door;

typedef struct	s_minimap
{
	t_f32		scale;
	t_f32		rotation;
	t_2d		offset;
	}				t_minimap;

typedef struct	s_obj
{
	t_s8	*nb;
	t_s32	size;
	t_s32	w;
	t_s32	h;
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
t_u32		*pal;
	t_u32		size;
}				t_palette;

typedef struct	s_player
{
	t_2d		ray;
	t_2d		pos;
	t_2d		direction;
	t_2d		plane;
t_f32			speed;
t_minimap	*m;
	}				t_player;

typedef struct	s_file
{
	t_s8	*str[14];
}				t_file;

typedef struct	s_animation
{
	t_s32	gun;
	t_u32	frame;
	t_u32	size;
}				t_animation;

typedef struct	s_raycaster
{
	t_2d_p	step;
	t_2d_p	map;
	t_2d	side_dist;
	t_2d	delta_dist;
	t_2d	plane;
	t_f32		perp_dist;
	t_s32	hit;
	t_s32	side;
}				t_raycaster;

typedef t_f32 (*funct)(t_raycaster * ray, t_player *player);

typedef struct	s_entity_render_info
{
	t_s32	sprite_size;
	t_2d_p	draw_start;
	t_2d_p	draw_end;
	t_2d_p	offset;
	t_s32	sprite_width_scale;
	t_s32	view;
}				t_entity_render_info;

typedef struct	s_items
{
	t_s32		id;
	t_2d		pos;
	t_2d		transformed_sprite_pos;
	t_s32		flag;
	t_s32		hp;
	t_texture	*tex;
}				t_items;

typedef struct	s_entity
{
	t_s32	nbr_of_entities;
	t_f32		*depth;
	t_s32	*order;
	t_items	*item;
}				t_entity;

typedef struct	s_m3x3
{
	float		e[3][3];
}				t_m3x3;

typedef struct	s_wolf
{
	funct		*dist;
	t_player	*player;
	t_obj		obj;
	t_u32		*img;
	t_mem		mem;
	t_s8		**map;
	t_door		*doors;
	t_u32		nbr_of_doors;
	t_u32		door_idx;
	t_texture	*tex;
	t_u32		flag;
	t_u8		res;
	t_animation	a;
	t_s32		view;
	t_entity	*entity;
	t_f32			*perp_dist;
	//t_2d		*minimap;
	t_2d		*p;
	t_m3x3	proj_matrix;
}				t_wolf;

typedef struct	s_ln
{
	t_2d	d;
	t_2d	s;
	int		p;
}				t_ln;


typedef struct	s_pts
{
	t_2d	min;
	t_2d	max;
}				t_pts;

t_m3x3			translate(t_m3x3 a, t_2d	offset);
t_m3x3			final_projection(t_wolf *wolf);
t_m3x3			rot(float angle);
t_m3x3			y_rot(float angle);
t_m3x3			scale(t_f32	scale);
t_m3x3			mx_mul(t_m3x3 a, t_m3x3 b);
t_m3x3			identity(void);
t_2d			transform(t_m3x3 a, t_2d p);
t_2d			find_center(t_wolf *wolf);
void			find_offset(t_wolf *wolf);
void			init_points(t_wolf *wolf);
void			background(t_wolf *wolf, t_u32 *img);
void			load_textures(t_wolf *wolf);
void			ft_wolf_init(t_wolf *wolf, t_sdl *sdl);
void			init_entities(t_entity *entity, t_wolf *wolf);
void			tex_to_mem(t_texture tex, t_wolf *wolf);
void			load_music(char *path, t_audio *audio);
void			draw_hud(t_wolf *wolf, t_u32 deltaframe);
t_2d_p			init_2d(t_s32 x, t_s32 y);
void			draw_sprite(t_wolf *wolf, t_2d_p start, t_texture tex, t_u32 size);
funct			*perp_dist(t_wolf *wolf);
t_f32				perp_distance_ew(t_raycaster *ray, t_player *player);
t_f32				perp_distance_sn(t_raycaster *ray, t_player *player);
t_f32				perp_distance_ew_door(t_raycaster *ray, t_player *player);
t_f32				perp_distance_sn_door(t_raycaster *ray, t_player *player);
t_f32				my_sin(t_f32 angle);
t_f32				my_cos(t_f32 angle);
t_f32				my_asin(t_f32 angle);
t_f32				my_acos(t_f32 angle);
t_f32				my_tan(t_f32 angle);
t_f32				my_atan(t_f32 angle);
t_f32				degree_radian(t_s32 degree);
t_f64				fov_calculator(t_wolf *wolf);
t_f64				ft_abs(t_f64 x);
t_s8			**int_to_tab(t_wolf *wolf);
t_s32			is_invalid(char *str);
t_s32			is_valid(t_f32 x, t_f32 y);
t_s32			tkneizer(t_s32 fd, t_wolf *wolf);
t_s32			lerp(t_f64 a, t_f32 t, t_f64 b);
t_s32			rgb_lerp(t_s32 color1, t_f32 t, t_s32 color2);
t_s32			direction_movement(t_wolf *wolf, t_s8 **map, t_s32 framedelta);
t_s32			print_map(char **map, t_obj obj, t_player *player, t_door *doors, t_wolf *wolf);
t_s32			mem_init(t_wolf *wolf, t_s32 ac, char **av);
void			draw_minimap(t_wolf *wolf);
void			palette(t_u32 *img, t_palette *p, t_u32 size);
void			check_flag(t_wolf *wolf, t_s8 **map, t_s32 framedelta);
void			set_flag(t_wolf *wolf, SDL_Event event);
void			ft_frametimes(t_s32 *frames, t_s32 *count);
void			event_handler(t_wolf *wolf, char **map, t_door *doors);
void			render(t_wolf *wolf);
void			raycast(t_wolf *wf);
void			calculate_distance(t_player *p, t_2d_p *a);
void			ft_raycast(t_wolf *wolf, t_player *player);
void			is_alloc(void *mem, t_wolf *wolf, t_s32 error);
void			draw_to_img(t_wolf wolf);
void			pers_keys(t_s32 keycode, t_wolf *wolf);
void			minimap(t_wolf *wolf);
void			mouse_movement(t_wolf *wolf, SDL_Event event);
void			draw_gun(t_wolf *wolf, t_u32 tex_id);
void			draw_machinegun(t_wolf *wolf, t_u32 deltaframe);
void			draw_wall(t_wolf *wf, t_s32 line_height, t_s32 x, t_raycaster *ray);
t_s32			lighting(t_s32 color, t_f32 distance);
t_texture		read_bmp(const t_s8 *filename, t_wolf *wolf, t_palette *pal);
void			entity_update(t_wolf *wf);
void			entity_draw_loop(t_wolf *wf, t_items *item, t_s32 *order, t_s32 nbr_of_entities);
void			sort_depth_buffer(t_entity *entity, t_items *item, t_player *player);
void			count_entities(t_s8 **map, t_obj obj, t_entity *entity);
#endif
