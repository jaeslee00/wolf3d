/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/27 06:08:30 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "draw.h"
# include <math.h>
# include <stdint.h>
# include <SDL2/SDL.h>
# define W (1280)
# define H (720)
# define HEIGHT 32
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define EW_WALL 0
# define SN_WALL 1
# define PRESSED 1
# define RELEASED 0
# define WALL 1
# define EW_DOOR 3
# define NS_DOOR 5
# define UP	1UL
# define DOWN	1UL << 1
# define RIGHT	1UL << 2
# define LEFT	1UL << 3
# define BMP_HEADER_SIZE 54
# ifndef PI32
#  define PI32 3.14159265359f
# endif

#include <stdio.h>

//TODO (jae) : Not sure if this is what you want to do lul
// NOTE(viccarau): That's exactly what I wanted, we'll see if you like it though.
//				I personally hate it how it looks and how it feels
typedef unsigned char	uint8;
typedef char			sint8;

typedef unsigned short int	uint16;
typedef short int			sint16;

typedef unsigned int	uint32;
typedef int				sint32;

typedef unsigned long int	uint64;
typedef long int			sint64;

typedef float			f32;
typedef double			f64;

/*
** E[ROW][COLUMN]
** ROW Major
*/

typedef struct	s_texture
{
	sint32			width;
	sint32			height;
	sint32			size;
	uint32_t		*data;
	}				t_texture;

typedef struct	s_2d_p
{
	sint32	x;
	sint32	y;
}				t_2d_p;

typedef struct	s_door
{
	t_2d_p	pos;
	uint8	flag;
}				t_door;

typedef struct	s_obj
{
	sint8*nb;
	sint32	size;
	sint32	len;
}				t_obj;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Renderer	*renderer;
	SDL_Event	event;
	SDL_Texture	*texture;
}				t_sdl;

typedef struct	s_player
{
	t_2d	ray;
	t_2d	pos;
	t_2d	offset;
	t_2d	direction;
	t_2d	plane;
	f32	speed;
	}				t_player;

typedef struct	s_raycaster
{
	t_2d_p	step;
	t_2d_p	map;
	t_2d	side_dist;
	t_2d	delta_dist;
	t_2d		plane;
	f64	perp_distance;
	//id_t	tex_flag;
	sint32	hit;
	sint32	side;
	f64	light;
}				t_raycaster;

typedef struct	s_wolf
{
	t_player	player;
	t_sdl		sdl;
	t_obj		obj;
	uint32		*img;
	t_mem		mem;
	sint8	**map;
	t_door		doors[100];
	sint32		nbr_of_doors;
	t_texture	tex[5];
	uint32		flag;
}				t_wolf;

void			ft_frametimes(sint32 *frames, sint32 *count);
sint32			direction_movement(t_wolf *wolf, char **map, sint32 frametime);
void			set_flag(t_wolf *wolf, SDL_Event event);
f64		fov_calculator(t_wolf *wolf);
sint32			print_map(char **map, t_obj obj, t_player *player, t_door *doors, t_wolf *wolf);
void			event_handler(t_wolf *wolf, char **map, t_door *doors);
void			render(t_wolf *wolf);
void			raycast(t_wolf *wf);
void			calculate_distance(t_player *p, t_2d_p *a);
void			ft_raycast(t_wolf *wolf, t_player *player);
sint8			**int_to_tab(t_wolf *wolf);
sint32			rgb_lerp(sint32 color1, f32 t, sint32 color2);

void			draw_minimap(t_wolf *wolf);
//sint32			lerp(int a, f32 t, int b);
f64			ft_abs(f64 x);
sint32			tkneizer(sint32 fd, t_wolf *wolf);
sint32			is_valid(f32 x, f32 y);
sint32			is_invalid(char *str);
void			mem_init(t_wolf *wolf);
void			is_alloc(void *mem, t_wolf wolf, sint32 error);
void			draw_to_img(t_wolf wolf);
void			pers_keys(sint32 keycode, t_wolf *wolf);
f32			my_sin(f32 angle);
f32			my_cos(f32 angle);
f32			my_asin(f32 angle);
f32			my_acos(f32 angle);
f32			my_tan(f32 angle);
f32			my_atan(f32 angle);
f32			degree_radian(sint32 degree);
void			minimap(t_wolf *wolf);

#endif
