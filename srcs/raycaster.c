/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:57:38 by viccarau          #+#    #+#             */

/*   Updated: 2019/07/30 15:57:38 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	verLine(int x, int y1, int y2, const int color, unsigned int *img)
{
	while (y1 < y2)
	{
		img[x + y1 * W] = color;
		y1++;
	}
	return (1);
}


int		set_color(int side, int x_side, int y_side, t_wolf *wf, int start, int end, int line_height, int x, t_raycaster ray)
{
	double	tex_width_scale;
	t_2d_p	tex_coord;
	int		tex_height_scale;
	int		tex_id;
	int		y;
	int	color;
	if (side == EW_WALL)
	{
		if (x_side < 0)
			tex_id = 0;
		else tex_id = 1;
	}
	else
	{
		if (y_side < 0)
			tex_id = 2;
		else
			tex_id = 3;
	}
	if (side == EW_WALL)
		tex_width_scale = wf->player.position.y + ray.perp_distance * wf->player.ray.y;
	else
		tex_width_scale = wf->player.position.x + ray.perp_distance * wf->player.ray.x;
	tex_width_scale = tex_width_scale - floor(tex_width_scale);
	tex_coord.x = (int)(tex_width_scale * (double)TEX_WIDTH);
	y = start;
	while (y < end)
	{
		if (line_height > 0)
		{
			tex_height_scale = y - H / 2 + line_height;
			tex_coord.y = ((tex_height_scale * TEX_WIDTH) / line_height) - 32; //TODO glitch on bottom-top texture of wall
			color = wf->tex[tex_id].data[TEX_WIDTH * tex_coord.y + tex_coord.x];
		}
		else color = 0;
		wf->img[x + y * W] = color;
		y++;
	}
	return (1);
}

void	raycast(t_wolf *wf)
{
	t_raycaster ray;
	int		hit;
	double	line_height;
	int		start;
	int		end;
	int		color;
	int		x = 0;

	x = 0;
	while (x < W)
	{
		hit = 0;
		wf->player.ray.x = wf->player.direction.x +  wf->player.plane.x * (2.0 * x / (double)W - 1.0);
		wf->player.ray.y = wf->player.direction.y + wf->player.plane.y * (2.0 * x / (double)W - 1.0);
		ray.delta_dist.x = fabs(1.0 / wf->player.ray.x);
		ray.delta_dist.y = fabs(1.0 / wf->player.ray.y);
		ray.map.x = (int)wf->player.position.x;
		ray.map.y = (int)wf->player.position.y;
		if (wf->player.ray.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (wf->player.position.x - ray.map.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (1.0 + ray.map.x - wf->player.position.x) * ray.delta_dist.x;
		}
		if (wf->player.ray.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (wf->player.position.y - ray.map.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (1.0 + ray.map.y - wf->player.position.y) * ray.delta_dist.y;
		}
		while (hit == 0)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.map.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.map.y += ray.step.y;
				ray.side = 1;
			}
			if (wf->map[ray.map.x][ray.map.y] > 0)
				hit = 1;
		}
		if (ray.side == 0)
			ray.perp_distance = (ray.map.x - wf->player.position.x + (1 - ray.step.x) / 2) / wf->player.ray.x;
		else
			ray.perp_distance = (ray.map.y - wf->player.position.y + (1 - ray.step.y) / 2) / wf->player.ray.y;
		line_height = (int)(H / ray.perp_distance);
		start = -line_height / 2 + H / 2;
		end = line_height / 2 + H / 2;
		if (start < 0)
			start = 0;
		if (end >= H)
			end = H - 1;
		color = set_color(ray.side, ray.step.x, ray.step.y, wf, start, end, line_height, x, ray);
		//color = 0xFFFF;
		//verLine(x, start, end, color, wf->img);
		x++;
	}

}
