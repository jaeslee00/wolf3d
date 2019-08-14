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
 
int	verLine(int x, int y1, int y2, const int color, unsigned int *img)
{
	int y;

	if (y2 < y1)
	{
		y1 += y2;
		y2 = y1 - y2;
		y1 -= y2;
	}
	if (y2 < 0 || y1 >= H  || x < 0 || x >= W)
		return (0);
	if (y1 < 0)
		y1 = 0;
	if (y2 >= W)
		y2 = H - 1;
	y = y1;
	while (y <= y2)
{
		img[x + y * W] = color;
		 y++;
	}
	return (1);
}

void	render(t_wolf *wolf, double dirX, double dirY, double planeX, double planeY)
{
for (int x = 0; x < W; x++)
		{

		double cameraX = 2 * x / (double)(W) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			int mapX = (int)wolf->player.position.x;
			int mapY = (int)wolf->player.position.y;
double sideDistX;
			double sideDistY;
double deltaDistX = ft_abs(1 / rayDirX);
			double deltaDistY = ft_abs(1 / rayDirY);
			double perpWallDist;
int stepX;
			int stepY;

			int hit = 0;
			int side; 
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (wolf->player.position.x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - wolf->player.position.x) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (wolf->player.position.y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - wolf->player.position.y) * deltaDistY;
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (wolf->map[mapX][mapY] == 1)
				hit = 1;
			}
			if (side == 0)
			perpWallDist = (mapX - wolf->player.position.x + (1 - stepX) / 2) / rayDirX;
			else
			perpWallDist = (mapY - wolf->player.position.y + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(H / perpWallDist);
int drawStart = -lineHeight / 2 + H / 2;
			if (drawStart < 0)
			drawStart = 0;
			int drawEnd = lineHeight / 2 + H / 2;
			if (drawEnd >= H)
			drawEnd = H - 1;
int color;

			if (wolf->map[mapX][mapY] == 1)
color = 0x660000;
else
color = 0;
			if (side == 1)
		color = color >> 1;
verLine(x, drawStart, drawEnd, color, wolf->img);
		}
	}
