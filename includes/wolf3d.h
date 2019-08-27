/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:46:58 by viccarau          #+#    #+#             */
/*   Updated: 2019/08/27 03:37:43 by jaelee           ###   ########.fr       */
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
typedef unsigned char	uint8;
typedef char			sint8;

typedef unsigned short int	uint16;
typedef short int			sint16;

typedef unsigned int	uint32;
typedef int				sint32;

typedef unsigned long int	uint64;
typedef long int			sint64;

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

typedef struct	s_door
{
	t_2d_p	pos;
	char	flag;
}				t_door;

typedef struct	s_obj
{
	char	*nb;
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
	t_2d	pos;
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
	id_t	tex_flag;
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
	char		**map;
	t_door		doors[100];
	int			nbr_of_doors;
	t_texture	tex[5];
	unsigned int flag;
}				t_wolf;

void			ft_frametimes(int *frames, int *count);
int				direction_movement(t_wolf *wolf, char **map, int frametime);
void			set_flag(t_wolf *wolf, SDL_Event event);
double		fov_calculator(t_wolf *wolf);
int				print_map(char **map, t_obj obj, t_player *player, t_door *doors, t_wolf *wolf);
void			event_handler(t_wolf *wolf, char **map, t_door *doors);
void			render(t_wolf *wolf);
void			raycast(t_wolf *wf);
void			calculate_distance(t_player *p, t_2d_p *a);
void			ft_raycast(t_wolf *wolf, t_player *player);
char			**int_to_tab(t_wolf *wolf);
int				rgb_lerp(int color1, float t, int color2);

void			draw_minimap(t_wolf *wolf);
//int				lerp(int a, float t, int b);
double		ft_abs(double x);
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
