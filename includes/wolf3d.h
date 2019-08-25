/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/24 08:12:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "draw.h"
# include <math.h>
# include <stdint.h>
# include <SDL2/SDL.h>
# define W 1280
# define H 720
# define FOV 80
# define HEIGHT 32
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define EW_WALL 0
# define SN_WALL 1
# define WALL_SIZE 64
# define PRESSED 1
# define RELEASED 0
# define BMP_HEADER_SIZE 54
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

typedef struct	s_texture
{
	int				width;
	int				height;
	int				size;
	uint32_t		*data;
	}				t_texture;

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
	t_2d	ray;
	t_2d	position;
	t_2d	offset;
	t_2d	direction;
	t_2d	plane;
	float	speed;
	}				t_player;

typedef struct	s_raycaster
{
	t_2d_p	step;
	t_2d_p	map;
	t_2d	side_dist;
	t_2d	delta_dist;
	t_2d		plane;
	double	perp_distance;
	int		hit;
	int		side;
	double	light;
}				t_raycaster;

typedef struct	s_wolf
{
	t_player	player;
	t_sdl		sdl;
	t_obj		obj;
	unsigned int	*img;
	t_mem		mem;
	int		**map;
t_texture	tex[4];
				unsigned int flag;
	}				t_wolf;

void ft_frametimes(int *frames, int *count);
int		direction_movement(t_wolf *wolf, int **map);
void	set_flag(t_wolf *wolf, SDL_Event event);
double fov_calculator(t_wolf *wolf);
int				print_map(int **map, t_obj obj, t_player *player);
void			render(t_wolf *wolf);
void			raycast(t_wolf *wf);
//render(t_wolf *wolf, double dirX, double dirY, double planeX, double planeY);
//render(&wolf, wolf.player.direction.x, wolf.player.direction.y, wolf.player.plane.x, wolf.player.plane.y);
void			calculate_distance(t_player *p, t_2d_p *a);
void			ft_raycast(t_wolf *wolf, t_player *player);
int			**int_to_tab(t_wolf *wolf);
int				rgb_lerp(int color1, float t, int color2);
int				lerp(int a, float t, int b);
double			ft_abs(double x);
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
