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

sint32		lighting(sint32 color, t_raycaster *ray)
{
	if(ray->perp_distance > 20)
		return (0);
	else if (ray->perp_distance > 10)
		ray->light = 0.2;
	else if (ray->perp_distance < 3)
		return (color);
	else
		ray->light = (1.0 - ray->perp_distance / 12.0);
	if (ray->light < 0.0)
		ray->light = 0.0;
	if (ray->light > 1.0)
		ray->light = 1.0;
	return (rgb_lerp(0.0, ray->light + 0.19f, color));
}

sint32		draw_wall(t_wolf *wf, sint32 line_height, sint32 x, t_raycaster *ray)
{
	t_2d_p	tex_coord;
	f32	tex_width_scale;
	sint32		tex_height_scale;
	sint32		tex_id;
	sint32		y;
	sint32	color;
	sint32	start;
	sint32	end;

	start = -line_height / 2 + H / 2;
	end = line_height / 2 + H / 2;
	if (start < 0)
		start = 0;
	if (end >= H)
		end = H - 1;
	if (ray->side == EW_WALL)
		tex_id = ray->step.x < 0 ? 0 : 1;
	else if (ray->side == 2 || ray->side == 3)
		tex_id = 4;
	else
		tex_id = ray->step.y < 0 ? 2 : 3;
	if (ray->side == EW_WALL || ray->side == 3)
		tex_width_scale = wf->player.pos.y + ray->perp_distance * wf->player.ray.y;
	else
		tex_width_scale = wf->player.pos.x + ray->perp_distance * wf->player.ray.x;
	tex_width_scale = tex_width_scale - floor(tex_width_scale);
	tex_coord.x = (sint32)(tex_width_scale * (f32)TEX_WIDTH);
	y = start;

	while (y < end)
	{
		tex_height_scale = y * 2 - H + line_height + 1;
		tex_coord.y = ((tex_height_scale * TEX_WIDTH) / line_height) / 2;
		color = wf->tex[tex_id].data[TEX_WIDTH * tex_coord.y + tex_coord.x];
		color = lighting(color, ray);
		wf->img[x + y * W] = color;
		y++;
	}
	return (1);
}

void	raycast(t_wolf *wf)
{
	t_raycaster	ray;
	sint32			hit;
	f32		line_height;
	sint32			x;
	f32		scale;

	scale = 2.0 / (f32)W;
	x = 0;
	while (x < W)
	{
		hit = 0;
		wf->player.ray.x = wf->player.direction.x +  wf->player.plane.x * (x * scale - 1.0);
		wf->player.ray.y = wf->player.direction.y + wf->player.plane.y * (x * scale - 1.0);
		ray.delta_dist.x = fabs(1.0 / wf->player.ray.x);
		ray.delta_dist.y = fabs(1.0 / wf->player.ray.y);
		ray.map.x = (sint32)wf->player.pos.x;
		ray.map.y = (sint32)wf->player.pos.y;
		if (wf->player.ray.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (wf->player.pos.x - ray.map.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (1.0 + ray.map.x - wf->player.pos.x) * ray.delta_dist.x;
		}
		if (wf->player.ray.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (wf->player.pos.y - ray.map.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (1.0 + ray.map.y - wf->player.pos.y) * ray.delta_dist.y;
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
			if (wf->map[ray.map.x][ray.map.y] == 1)
			{
				hit = 1;
			}
			if (wf->map[ray.map.x][ray.map.y] == EW_DOOR)
			{
				//TODO (jae): need a working condition... getting better though!!
				if (ray.side_dist.x < ray.side_dist.y - 0.5)
					continue ;
				else
				{
					hit = 1;
					ray.side = 2;
				}
			}
			if (wf->map[ray.map.x][ray.map.y] == NS_DOOR)
			{
				//TODO (jae): need a working condition... getting better though!!
				if (ray.side_dist.y < ray.side_dist.x - 0.5)
					continue ;
				else
				{
					hit = 1;
					ray.side = 3;
				}
			}
		}
		if (ray.side == 0)
			ray.perp_distance = (ray.map.x - wf->player.pos.x + (1 - ray.step.x) / 2) / wf->player.ray.x;
		else if (ray.side == 1)
			ray.perp_distance = (ray.map.y - wf->player.pos.y + (1 - ray.step.y) / 2) / wf->player.ray.y;
		else if (ray.side == 2)
			ray.perp_distance = (ray.map.y + 0.5 - wf->player.pos.y) / wf->player.ray.y;
		else if (ray.side == 3)
			ray.perp_distance = (ray.map.x + 0.5 - wf->player.pos.x) / wf->player.ray.x;
		line_height = (sint32)((f32)H / ray.perp_distance);
		if (line_height > 1)
			draw_wall(wf, line_height, x, &ray);
		x++;
	}
}
