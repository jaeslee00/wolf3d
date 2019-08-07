/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/04 16:56:25 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "draw.h"
# include <math.h>
# include <SDL2/SDL.h>
# define W 640
# define H 360
# define FOV 80
# define HEIGHT 32
# define WALL_SIZE 64
# ifndef PI32
#  define PI32 3.14159265359f
# endif

#define ANGLE0 0
#define ANGLE5 W / 16
#define ANGLE10 ANGLE5 * 2
#define ANGLE20 ANGLE10 * 2
#define ANGLE30 ANGLE10 * 3
#define ANGLE40 ANGLE20 * 2
#define ANGLE60 ANGLE20 * 3
#define ANGLE80 ANGLE40 * 2
#define ANGLE90 ANGLE30 * 3
#define ANGLE180 ANGLE90 * 2
#define ANGLE270 ANGLE180 + ANGLE90
#define ANGLE360 ANGLE180 * 2


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

typedef struct	s_player
{
	t_2d_p	ray;
t_2d_p	position;
t_2d direction;
	t_2d plane;
	float arc;
	int distance;
	int height;
	int speed;
}				t_player;

typedef struct	s_wolf
{
	t_player	player;
	t_sdl		sdl;
	t_obj		obj;
	unsigned int	*img;
	t_mem		mem;
}				t_wolf;

typedef struct	s_steps
{
	float	x_step[5761];
	float	y_step[5761];
	float	correction[961];
}				t_steps;

void			render(t_wolf *wolf, t_steps *s, t_obj *o, int **map);
void			init_precalc(t_steps *steps);
void			calculate_distance(t_player *p, t_2d_p *a);
void			ft_raycast(t_wolf *wolf, t_player *player);
int				**int_to_tab(t_obj obj);
int				rgb_lerp(int color1, float t, int color2);
int				lerp(int a, float t, int b);
int				ft_abs(int x);
int				tkneizer(int fd, t_wolf *wolf);
int				is_valid(float x, float y);
int				is_invalid(char *str);
void			mem_init(t_wolf *wolf);
void			is_alloc(void *mem, t_wolf wolf, int error);
void			draw_to_img(t_wolf wolf);
void			pers_keys(int keycode, t_wolf *wolf);
float			my_sin(float angle);
float			my_cos(float angle);
float			my_asin(float angle);
float			my_acos(float angle);
float			my_tan(float angle);
float			my_atan(float angle);
float			degree_radian(int degree);

#endif
 