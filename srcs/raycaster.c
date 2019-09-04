/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:57:38 by viccarau          #+#    #+#             */
/*   Updated: 2019/09/04 11:53:29 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	raycast_collision(sint8 **map, t_raycaster *ray, int *hit)
{
	if (map[ray->map.y][ray->map.x] == 1)
		*hit = 1;
	else if (map[ray->map.y][ray->map.x] == 3)
	{
		if (ray->side_dist.x < ray->side_dist.y + 0.5f)
		{
			*hit = 1;
			ray->side = 3;
		}
	}
	else if (map[ray->map.y][ray->map.x] == 5)
	{
		if (ray->side_dist.y < ray->side_dist.x + 0.5f)
		{
			*hit = 1;
			ray->side = 2;
		}
	}
}

sint32	dda_raycast(t_wolf *wf, t_raycaster *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		raycast_collision(wf->map, ray, &hit);
	}
	return (ray->side);
}

void	dda_init(t_raycaster *ray, t_player p)
{
	ray->delta_dist.x = fabs(1.0f / p.ray.x);
	ray->delta_dist.y = fabs(1.0f / p.ray.y);
	ray->map.x = (sint32)p.pos.x;
	ray->map.y = (sint32)p.pos.y;
	if (p.ray.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (p.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (1.0f + ray->map.x - p.pos.x) * ray->delta_dist.x;
	}
	if (p.ray.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (p.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (1.0f + ray->map.y - p.pos.y) * ray->delta_dist.y;
	}
}

//TODO (jae) : need a y-depth buffer to sort order of rendering npc, objects
//TODO (jae) : sorting-algorithm needed.. depth_buffer[0 ... nbr_of_npc] = npc_id;
//TODO (jae) : need a condition to call draw_enemy() for only those are within the player's view for optimization

void	draw_npc(t_wolf *wf)
{
	t_player pl;
	pl = wf->player;
	// sint32	npc_array[100]; // variable inside the array is npc_id;
	// sint32	npc_idx = 0;
	// depth_sort(npc_array, wf->npc);
	// while (npc_idx < nbr_of_npc)
	// {
	// 		relative_enemy_pos.x = wf->npc[npc_array[npx_idx]].pos.x - pl.pos.x;
	// 		relative_enemy_pos.y = wf->npc[npc_array[npx_idx]].pos.y - pl.pos.y;
	// 		.......
	//		npc_idx++;
	// }
	t_2d	relative_npc_pos;
	//TODO (jae) : Store these info in npc_structure to use it for rendering
	relative_npc_pos.x = wf->npc[0].pos.x - pl.pos.x;
	relative_npc_pos.y = wf->npc[0].pos.y - pl.pos.y;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	f32		inverse_determinant = 1.0f / (pl.plane.x * pl.direction.y - pl.plane.y * pl.direction.x);
	t_2d	transformed_sprite_pos;

	transformed_sprite_pos.x = inverse_determinant * (pl.direction.y * relative_npc_pos.x - pl.direction.x * relative_npc_pos.y);
	transformed_sprite_pos.y = inverse_determinant * (-pl.plane.y * relative_npc_pos.x + pl.plane.x * relative_npc_pos.y);

	sint32	sprite_height = abs((sint32)((f32)H / transformed_sprite_pos.y));
	sint32	sprite_width = sprite_height;
	sint32	sprite_pos_screen = (sint32)(((f32)W) * (1.0f + transformed_sprite_pos.x / transformed_sprite_pos.y));

	t_2d_p	draw_start;
	t_2d_p	draw_end;

	draw_start.y = -sprite_height / 2 + H / 2 - wf->view;
	draw_end.y = sprite_height / 2 + H / 2 - wf->view;
	if (draw_start.y < 0)
		draw_start.y = 0;
	if (draw_end.y >= H)
		draw_end.y = H - 1;

	draw_start.x = -sprite_width / 2 + sprite_pos_screen / 2;
	draw_end.x = sprite_width / 2 + sprite_pos_screen / 2;
	sint32	x_offset = 0;
	if (draw_start.x < 0)
	{
		x_offset = draw_start.x;
		draw_start.x = 0;
	}
	if (draw_end.x >= W)
		draw_end.x = W - 1;

	sint32	x;
	sint32	y;
	t_2d_p	tex_coord;
	sint32	tex_width_scale;
	sint32	tex_height_scale;
	sint32	color;

	x = draw_start.x;
	while (x < draw_end.x)
	{
		tex_width_scale = x - draw_start.x - x_offset;
		tex_coord.x = tex_width_scale * wf->npc[0].tex->width / sprite_width;
		y = draw_start.y;
		while (y < draw_end.y)
		{
			tex_height_scale = (y + wf->view) * 2 - H + sprite_height;
			tex_coord.y =
				((tex_height_scale * wf->npc[0].tex->height) / sprite_height) / 2;
			if (transformed_sprite_pos.y > 0 && (transformed_sprite_pos.y < wf->perp_dist[x]))
			{
				if (wf->npc[0].tex->data[tex_coord.x + tex_coord.y * wf->npc[0].tex->width] != NPC_BLANK)
				{
					color = wf->npc[0].tex->data[tex_coord.x + tex_coord.y * wf->npc[0].tex->width];
					wf->img[x + y * W] = lighting(color, transformed_sprite_pos.y);
				}
			}
			y++;
		}
		x++;
	}
}

void	raycast(t_wolf *wf)
{
	t_raycaster	ray;
	f32			line_height;
	sint32		x;
	f32			scale;

	scale = 2.0f / (f32)W;
	x = 0;
	while (x < W)
	{
		wf->player.ray.y = wf->player.direction.y +
			wf->player.plane.y * (x * scale - 1.0f); // cam_width to be -1 to 1
		wf->player.ray.x = wf->player.direction.x +
			wf->player.plane.x * (x * scale - 1.0f);
		dda_init(&ray, wf->player);
		dda_raycast(wf, &ray);
		ray.perp_dist = wf->dist[ray.side](&ray, wf->player);
		wf->perp_dist[x] = ray.perp_dist;
		line_height = (sint32)((f32)H / ray.perp_dist);
		if (line_height > 1)
			draw_wall(wf, line_height, x, &ray);
		x++;
	}
	draw_npc(wf);
}
