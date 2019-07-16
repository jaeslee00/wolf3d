/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 04:25:32 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/16 23:52:13 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
int		my_function(int keycode, t_fdf *fdf)
{
	pers_keys(keycode, fdf);
	key_to_camera(keycode, fdf);
	if (keycode == KEY_R)
	{
		fdf->zscale = 0.1f;
		ft_bzero(&fdf->offset, sizeof(fdf->offset));
	}
	if (keycode == KEY_ESCAPE)
		is_alloc(NULL, *fdf, 0);
	if (keycode == KEY_SPACEBAR)
	{
		if (fdf->flags & ISO_PROJ)
			fdf->flags &= ~(ISO_PROJ);
		else
			fdf->flags |= ISO_PROJ + ORTH_PROJ;
	}
	fdf->proj_matrix = final_projection(fdf);
	draw_to_img(*fdf);
	//mlx_put_image_to_window(fdf->mlx.mlx,fdf->mlx.win, fdf->mlx.img, 0, 0);
	if ((fdf->flags & 0x4) == 0)
		ui_instructions(*fdf);
	return (1);
}

int		mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 5)
		if ((fdf->scale - 1 * fdf->multi) > 0)
			fdf->scale -= 1 * fdf->multi;
	if (button == 4)
		fdf->scale += 1 * fdf->multi;
	fdf->proj_matrix = final_projection(fdf);
	draw_to_img(*fdf);
	//mlx_put_image_to_window(fdf->mlx.mlx,fdf->mlx.win, fdf->mlx.img, 0, 0);
	if ((fdf->flags & 0x4) == 0)
		ui_instructions(*fdf);
	return (0);
}
*/

/*void	ft_mlx_init(t_fdf *fdf, t_img img)
{
	//is_alloc((fdf->mlx.mlx = mlx_init()), *fdf, -3);
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, W, H);
	fdf->str = (int *)mlx_get_data_addr(fdf->mlx.img, &img.bpx,
										&img.size_line, &img.endian);
	is_alloc((fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, W, H,
											"MY_WINDOW")), *fdf, -4);
	fdf->scale = calculate_scale(*fdf);
	fdf->proj_matrix = final_projection(fdf);
}*/

int		main(int ac, char **av)
{
	t_fdf	fdf;
	t_img	img;
	int		fd;

	SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* win = SDL_CreateWindow("GAME", 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       W, H, 0);
		(void)win;
	mem_init(&fdf, &img);
	fd = open(av[1], O_RDONLY);
	if (ac && fd > 0)
	{
		if (tkneizer(fd, &fdf))
		{
			fdf.p = int_to_points(fdf);
			//initialize_cam(&fdf);
			//ft_mlx_init(&fdf, img);
			//draw_to_img(fdf);
			//mlx_put_image_to_window(fdf.mlx.mlx, fdf.mlx.win,fdf.mlx.img, 0, 0);
			//ui_instructions(fdf);
			//mlx_hook(fdf.mlx.win, 2, 1L << 0, &my_function, &fdf);
			//mlx_mouse_hook(fdf.mlx.win, &mouse_hook, &fdf);
			//mlx_loop(fdf.mlx.mlx);
		}
	}
	while (1);
	return (0);
}
