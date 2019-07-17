/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:07:39 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/17 23:47:59 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "cl_helper.h"
# include "libft.h"
# include "camera.h"
# include "draw.h"
# include <mlx.h>
# include <math.h>
# include <SDL2/SDL.h>
# define W 1200
# define H 1200
# ifndef PI32
#  define PI32 3.14159265359f
# endif

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

typedef struct	s_img
{
	int		bpx;
	int		size_line;
	int		endian;
}				t_img;

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

# define ORTH_PROJ 0x1
# define ISO_PROJ 0x2

typedef struct	s_fdf
{
	t_pts		pts;
	t_min_max	l;
	t_3d		offset;
	t_mem		mem;
	char		flags;
	t_obj		obj;
	unsigned int	*str;
	t_cam		cam;
	t_camloc	loc;
	t_sdl		sdl;
	t_4d		*p;
	float		scale;
	float		zscale;
	float		multi;
	t_m4x4		proj_matrix;
}				t_fdf;

int				rgb_lerp(int color1, float t, int color2);
int				lerp(int a, float t, int b);
int				ft_abs(int x);
int				tkneizer(int fd, t_fdf *fdf);
int				calculate_scale(t_fdf fdf);
int				is_valid(float x, float y);
int				is_invalid(char *str);
t_m4x4_inv		camera_transform(t_3d x, t_3d y, t_3d z, t_3d p);
t_m4x4_inv		ortho_proj(float wheight, float near, float far);
t_m4x4_inv		pers_proj(float woh, float focallength,
					  float nearcliplane, float farclipplane);
void			initialize_cam(t_fdf *fdf);
void			rotate(t_fdf *fdf, float angle, t_m4x4 f(float));
void			ui_instructions(t_fdf fdf);
void			mem_init(t_fdf *fdf);
void			mi(t_fdf fdf, int x, int y, char *str);
void			is_alloc(void *mem, t_fdf fdf, int error);
void			draw_to_img(t_fdf fdf);
void			pers_keys(int keycode, t_fdf *fdf);
void			key_to_camera(int keycode, t_fdf *fdf);
void			range_finder(t_fdf *fdf);
float			range(float min, float max, float value);
float			my_sin(float angle);
float			my_cos(float angle);
t_cam			get_standard_camera(void);
t_3d			find_center(t_fdf fdf);
t_4d			*int_to_points(t_fdf fdf);
t_4d			point(float x, float y, float z, float w);
t_4d			transform(t_m4x4 a, t_4d p);
t_m4x4			translate(t_m4x4 a, t_3d t);
t_m4x4			cam_obj_matrix(t_fdf fdf);
t_m4x4			x_rot(float angle);
t_m4x4			y_rot(float angle);
t_m4x4			z_rot(float angle);
t_m4x4			translation(t_3d t);
t_m4x4			identity(void);
t_m4x4			mx_mul(t_m4x4 a, t_m4x4 b);
t_m4x4			scaling(float s);
t_m4x4			z_scaling(float s);
t_m4x4			final_projection(t_fdf *fdf);
t_ln			init_ln(t_pts pts);
#endif
