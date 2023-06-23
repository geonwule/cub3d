/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:18:48 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/23 12:10:56 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>


extern char	map[15][34]; //tmp

void verLine(t_vars *vars, int x, int y1, int y2, int color)
{
	int y;

	y = y1;

	// printf("y1 = %d, y2 = %d\n", y1, y2);
	while (y <= y2)
	{
		mlx_pixel_put(vars->mlx, vars->win, x, y, color);
		y++;
	}
}

void calc(t_vars *vars, int x)
{
	t_info	*info = vars->info;
	double cameraX = 2 * x / (double)WIN_WIDTH - 1;
	double rayDirX = info->dirX + info->planeX * cameraX;
	double rayDirY = info->dirY + info->planeY * cameraX;

	int mapX = (int)info->posX;
	int mapY = (int)info->posY;

	double sideDistX;
	double sideDistY;

	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	double perWallDist;

	int stepX;
	int stepY;

	int hit = 0;
	int side;
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (info->posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (info->posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
	}

	while (hit == 0)
	{
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
		if (map[mapX][mapY] == '1' || map[mapX][mapY] == '2' \
			|| map[mapX][mapY] == '3' || map[mapX][mapY] == 'B' || map[mapX][mapY] == 'M')
			hit = 1;

	}
	if (map[mapX][mapY] == 'M')
	{
		vars->m_pos[X] = mapX;
		vars->m_pos[Y] = mapY;
		vars->monster_come = 1;
	}

	if (side == 0)
		perWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
	else
		perWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

	int lineHeight = (int)(WIN_HEIGHT / perWallDist);

	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;

	int	tex_num;
	if (map[mapX][mapY] == '1')
		tex_num = 0;
	else if (map[mapX][mapY] == '2')
		tex_num = 1;
	else if (map[mapX][mapY] == '3')
		tex_num = 2;
	else if (map[mapX][mapY] == 'B')
		tex_num = 3;
	else if (map[mapX][mapY] == 'M')
		tex_num = 4;

	// calculate value of wallX
	double	wallX;
	if (side == 0)
		wallX = info->posY + perWallDist * rayDirY;
	else
		wallX = info->posX + perWallDist * rayDirX;
	wallX -= floor(wallX);

	// x coordinate on the texture

	int texX = (int)(wallX * (double)TEX_WIDTH);
	if (side == 0 && rayDirX > 0)
		texX = TEX_WIDTH - texX - 1;
	if (side == 1 && rayDirY < 0)
		texX = TEX_WIDTH - texX - 1;

	// how much to increase the texture coordinate perscreen pixel
	double	step = 1.0 * TEX_HEIGHT / lineHeight;

	// starting texture coordinate
	double	texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
	for (int y = drawStart; y < drawEnd; y++)
	{
		// cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos % (TEX_HEIGHT - 1); // & -> % AND연산자에서 %로
		texPos += step;

		int color = info->texture[tex_num][TEX_HEIGHT * texY + texX];

		// make color darker for y-sides : R, G and B byte each divided through two with a "shift" and an "and"
		if (side == 1)
			color = (color >> 1) & 8355711;

		info->buf[y][x] = color;
	}

	//SPRITE CASTING
	// //sort sprites from far to close
	// for(int i = 0; i < numSprites; i++)
	// {
	// 	spriteOrder[i] = i;
	// 	spriteDistance[i] = ((info->posX - sprite[i].x) * (info->posX - sprite[i].x) + (info->posY - sprite[i].y) * (info->posY - sprite[i].y)); //sqrt not taken, unneeded
	// }
	// sortSprites(spriteOrder, spriteDistance, numSprites);
	// //after sorting the sprites, do the projection and draw them
	// for(int i = 0; i < numSprites; i++)
	// {
	// 	//translate sprite position to relative to camera
	// 	double spriteX = sprite[spriteOrder[i]].x - info->posX;
	// 	double spriteY = sprite[spriteOrder[i]].y - info->posY;

	// 	//transform sprite with the inverse camera matrix
	// 	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// 	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// 	// [ planeY   dirY ]                                          [ -planeY  planeX ]

	// 	double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

	// 	double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
	// 	double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

	// 	int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));

	// 	//parameters for scaling and moving the sprites
	// 	#define uDiv 1
	// 	#define vDiv 1
	// 	#define vMove 0.0
	// 	int vMoveScreen = (int)(vMove / transformY);

	// 	//calculate height of the sprite on screen
	// 	int spriteHeight = (int)fabs((WIN_HEIGHT / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
	// 	//calculate lowest and highest pixel to fill in current stripe
	// 	int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
	// 	if(drawStartY < 0) drawStartY = 0;
	// 	int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
	// 	if(drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;

	// 	//calculate width of the sprite
	// 	int spriteWidth = (int)fabs((WIN_HEIGHT / transformY) / uDiv);
	// 	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	// 	if(drawStartX < 0) drawStartX = 0;
	// 	int drawEndX = spriteWidth / 2 + spriteScreenX;
	// 	if(drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;

	// 	//loop through every vertical stripe of the sprite on screen
	// 	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	// 	{
	// 		int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
	// 		//the conditions in the if are:
	// 		//1) it's in front of camera plane so you don't see things behind you
	// 		//2) it's on the screen (left)
	// 		//3) it's on the screen (right)
	// 		//4) ZBuffer, with perpendicular distance
	// 		if(transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && transformY < info->zBuffer[stripe])
	// 		for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
	// 		{
	// 			int d = (y-vMoveScreen) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
	// 			int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
	// 			int color = info->texture[sprite[spriteOrder[i]].texture][TEX_WIDTH * texY + texX]; //get current color from the texture
	// 			if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
	// 		}
	// 	}
	// }

#ifdef MAP_DEBUG
	printf("side = %d\n", side);
	printf("perwallDist %f\n", perWallDist);
	if (side == 0)
	{
		printf("perWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX\n");
		printf("mapX = %d posX = %f stepX = %d rayDirx = %f\n", mapX, info->posX, stepX, rayDirX);
	}		
	else
	{
		printf("perWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY\n");
		printf("mapY = %d posY = %f stepY = %d rayDirY = %f\n", mapY, info->posY, stepY, rayDirY);
	}
	printf("line_height = %d\n", lineHeight);
	printf("drawStart = %d\ndraw_end = %d\n", drawStart, drawEnd);
	printf("mapX = %d mapY = %d\n", mapX, mapY);
#endif
}

void map_set(t_vars *vars)
{
	int x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		calc(vars, x);
		x++;
	}
}
