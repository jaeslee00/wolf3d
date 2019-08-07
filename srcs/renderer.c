/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:16:29 by viccarau          #+#    #+#             */

/*   Updated: 2019/08/01 13:18:39 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_rect(int x, int y, int width, int height, unsigned int *img)
{
	int i;
	int j;

	i = x;
	while (i < height + x)
	{
		j = y;
		while (j < width + y)
		{
			if ((j + i * W) < W * H && (j + i * W) > 0)
			{
				img[j + i * W] = 1000;
			}
			j++;
		}
		i++;
	}
}

void	render(t_wolf *wolf, t_steps *s, t_obj *o, int **map)
{
	int vertical_grid;
int horizontal_grid;
int next_v_grid;
int dist_h_grid;
float x_inter;
	float y_inter;
float next_x_inter;
float next_y_inter;

int x_grids_index;
int y_grids_index;

float distToVerticalGridBeingHit;
float distToHorizontalGridBeingHit;

int cast_angle, cast_column;

cast_angle = wolf->player.arc;
cast_angle -= (W / 2);

if (cast_angle < 0)
cast_angle = ANGLE360 + cast_angle;
for (cast_column = 0; cast_column < W; cast_column += 5)
{
	if (cast_angle > 0 && cast_angle < ANGLE180)
	{
			horizontal_grid = (wolf->player.position.x / 64) * 64  + 64;
dist_h_grid = 64;
			float xtemp = my_tan(degree_radian(cast_angle) * (horizontal_grid - wolf->player.position.y));
			x_inter = xtemp + wolf->player.position.x;
	}
	else
	{
			horizontal_grid = (wolf->player.position.y / 64) * 64;
        dist_h_grid = -64;

			float xtemp = my_tan(degree_radian(cast_angle)) * (horizontal_grid - wolf->player.position.y);
			x_inter = xtemp + wolf->player.position.x;

        horizontal_grid--;
	}
	// LOOK FOR HORIZONTAL WALL
		if (cast_angle == 0 || cast_angle == ANGLE180)
			distToHorizontalGridBeingHit = 9999999.0f;
	else
	{
			next_x_inter = s->x_step[cast_angle];
        while (1)
        {
			x_grids_index = (int)(x_inter / 64);
			// in the picture, y_grids_index will be 1
			y_grids_index = (horizontal_grid / 64);

			if ((x_grids_index >= o->len) ||
					(y_grids_index >= o->size / o->len) ||
				x_grids_index < 0 || y_grids_index < 0)
			{
					distToHorizontalGridBeingHit = 9999999.0f;
				break;
			}
				else if ((map[y_grids_index][x_grids_index]) != 0 )
			{
					distToHorizontalGridBeingHit  = (x_inter- wolf->player.position.x)* my_cos(degree_radian(cast_angle));
				break;
			}
			else
			{
				x_inter += next_x_inter;
				horizontal_grid += dist_h_grid;
			}
        }
	}

		if (cast_angle < ANGLE90 || cast_angle > ANGLE270)
	{
			vertical_grid = 64 + (wolf->player.position.x / 64) * 64;
        next_v_grid = 64;

			float ytemp = my_tan(degree_radian(cast_angle)) * (vertical_grid - wolf->player.position.x);
			y_inter = ytemp + wolf->player.position.y;
	}
	else
	{
			vertical_grid = (wolf->player.position.x / 64) * 64;
        next_v_grid = -64;

			float ytemp = my_tan(degree_radian(cast_angle)) * (vertical_grid - wolf->player.position.x);
			y_inter = ytemp + wolf->player.position.y;

        vertical_grid--;
	}
		if (ANGLE90 || ANGLE270)
		distToVerticalGridBeingHit = 9999999.0f;
		else
	{
        next_y_inter = s->y_step[cast_angle];
        while (1)
        {
			x_grids_index = (vertical_grid / 64);
			y_grids_index = (int)(y_inter / 64);

				if ((x_grids_index >= o->len) ||
					(y_grids_index >= o->size / o->len) ||
				x_grids_index < 0 || y_grids_index < 0)
			{
					distToVerticalGridBeingHit = 9999999.0f;
				break;
			}
				else if ((map[y_grids_index][x_grids_index]) != 0)
			{
					distToVerticalGridBeingHit = (y_inter - wolf->player.position.y) * my_sin(degree_radian(cast_angle));
				break;
			}
			else
			{
				y_inter += next_y_inter;
				vertical_grid += next_v_grid;
			}
        }
	}

	float dist;
	int topOfWall;
	int bottomOfWall;
		
		if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
		dist = distToHorizontalGridBeingHit;
			else
		dist = distToVerticalGridBeingHit;
			//dist /= s->correction[cast_column];
	int projectedWallHeight = (int)(64 * (float)426 / dist);
	bottomOfWall = 360 + (int)(projectedWallHeight * 0.5f);
	topOfWall = H - bottomOfWall;
	if (bottomOfWall >= H)
		bottomOfWall = H - 1;
	//fOffscreenGraphics.drawLine(cast_column, topOfWall, cast_column, bottomOfWall);
		//fOffscreenGraphics.fillRect(castColumn, topOfWall, 5, projectedWallHeight);
		//if (cast_column > 0 && topOfWall > 0 && bottomOfWall > 0 && cast_column < 720 && topOfWall < 720 && bottomOfWall < 720)
			fill_rect(cast_column, topOfWall, 5, projectedWallHeight, wolf->img);
		//(void)topOfWall;
		//fill_rect(0, 0, 100, 100, wolf->img);
		//fill_rect(150, 150, 100, 100, wolf->img);
		//fill_rect(500, 500, 100, 100, wolf->img);

		//fillRect(int x, int y, int width, int height)
		cast_angle += 5;
		if (cast_angle >= (W / 4) * 18)
			cast_angle -= (W / 4) * 18;
}
	// blit to screen
}