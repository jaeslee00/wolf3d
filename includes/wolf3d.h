/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/27 22:37:19 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "camera.h"
# include "draw.h"
# include <math.h>
# include <SDL2/SDL.h>
# define W 900
# define H 900
# ifndef PI32
#  define PI32 3.14159265359f
# endif

#include <stdio.h>
typedef struct	s_ilst
{
	int				content;
	struct s_ilst	*next;
}				t_ilst;

/*
** E[ROW][COLUMN]
** ROW Major
*/

typedef struct	s_2d_p
{
	int		x;
	int		y;
}				t_2d_p;

typedef struct	s_m4x4_i
{
	t_m4x4	forward;
	t_m4x4	inverse;
}				t_m4x4_inv;

typedef struct	s_pts
{
	t_2d	min;
	t_2d	max;
}				t_pts;

typedef struct	s_min_max
{
	int		min;
	int		max;
}				t_min_max;

typedef struct	s_ln
{
	t_2d	d;
	t_2d	s;
	int		p;
}				t_ln;

typedef struct	s_obj
{
	int		*nb;
	int		size;
	int		len;
}				t_obj;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Renderer	*renderer;
	SDL_Event	event;
	SDL_Texture	*texture;
}				t_sdl;

typedef struct	s_wolf
{
	t_sdl		sdl;
	t_obj		obj;
	unsigned int	*img;
	t_mem		mem;
}				t_wolf;

typedef struct	s_player
{
	t_2d position;
	t_2d direction;
	t_2d plane;

}				t_player;


int				**int_to_tab(t_obj obj);
int				rgb_lerp(int color1, float t, int color2);
int				lerp(int a, float t, int b);
int				ft_abs(int x);
int				tkneizer(int fd, t_wolf *wolf);
int				calculate_scale(t_wolf wolf);
int				is_valid(float x, float y);
int				is_invalid(char *str);
t_m4x4_inv		camera_transform(t_3d x, t_3d y, t_3d z, t_3d p);
t_m4x4_inv		pers_proj(float woh, float focallength,
					  float nearcliplane, float farclipplane);
void			initialize_cam(t_wolf *wolf);
void			rotate(t_wolf *wolf, float angle, t_m4x4 f(float));
void			ui_instructions(t_wolf wolf);
void			mem_init(t_wolf *wolf);
void			mi(t_wolf wolf, int x, int y, char *str);
void			is_alloc(void *mem, t_wolf wolf, int error);
void			draw_to_img(t_wolf wolf);
void			pers_keys(int keycode, t_wolf *wolf);
void			range_finder(t_wolf *wolf);
float			range(float min, float max, float value);
float			my_sin(float angle);
float			my_cos(float angle);
t_cam			get_standard_camera(void);
t_4d			*int_to_points(t_wolf wolf);
t_4d			point(float x, float y, float z, float w);
t_4d			transform(t_m4x4 a, t_4d p);
t_m4x4			translate(t_m4x4 a, t_3d t);
t_m4x4			x_rot(float angle);
t_m4x4			y_rot(float angle);
t_m4x4			z_rot(float angle);
t_m4x4			translation(t_3d t);
t_m4x4			identity(void);
t_m4x4			mx_mul(t_m4x4 a, t_m4x4 b);
t_m4x4			scaling(float s);
t_m4x4			z_scaling(float s);
t_m4x4			final_projection(t_wolf *wolf);
t_ln			init_ln(t_pts pts);
#endif
