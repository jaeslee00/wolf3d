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
	if (y2 < y1) {y1 += y2; y2 = y1 - y2; y1 -= y2;} //swap y1 and y2
	if (y2 < 0 || y1 >= H  || x < 0 || x >= W) return 0; //no single point of the line is on screen
	if (y1 < 0) y1 = 0; //clip
	if (y2 >= W) y2 = H - 1; //clip

	//printf("%d %d %d\n", x, y1, y2);
	for(int y = y1; y <= y2; y++)
		img[x + y * W] = color;
	return (1);
}

void	render(t_wolf *wolf, double dirX, double dirY, double planeX, double planeY)
{
	double posX = 3, posY = 3;  //x and y start position
	
	for (int x = 0; x < W; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / W - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)posX;
			int mapY = (int)posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = abs(1 / rayDirX);
			double deltaDistY = abs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
				//Check if ray has hit a wall
				if (wolf->map[mapX][mapY] == 1) hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(H / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + H / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + H / 2;
			if(drawEnd >= H)drawEnd = H - 1;

			//choose wall color
			 int color;

			if (wolf->map[mapX][mapY] == 1)
color = 1000;
else
color = 0;
			//give x and y sides different brightness
			if (side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color, wolf->img);
		}
	}