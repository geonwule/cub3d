
// void	mini_map(t_info *info)
// {
// 	int mini_width = WIDTH / 4;
// 	int mini_height = HEIGHT / 4;
// 	void	*mini = mlx_new_image(info->mlx, mini_width, mini_height);
// 	int a;
// 	int	*data = (int *)mlx_get_data_addr(mini, &a, &a, &a);
// 	for (int y = 0; y < 24; y++)
// 	{
// 		for (int x = 0; x < 24; x++)
// 		{
// 			if (worldMap[y][x] == 0)
// 			{//empty
// 				for (int a = y; a < mini_height / 24 * y; a++)
// 				{
// 					for (int b = x; b < mini_width / 24 * x; b++)
// 					{
// 						data[a * WIDTH + b] = 0x000000;
// 					}
// 				}
// 			}
// 			else if (x == info->posX && y == info->posY)
// 			{//player
// 				for (int a = y; a < mini_height / 24 * y; a++)
// 				{
// 					for (int b = x; b < mini_width / 24 * x; b++)
// 					{
// 						data[a * WIDTH + b] = 0xFFFF00;
// 					}
// 				}
// 			}
// 			else
// 			{//wall
// 				for (int a = y; a < mini_height / 24 * y; a++)
// 				{
// 					for (int b = x; b < mini_width / 24 * x; b++)
// 					{
// 						data[a * WIDTH + b] = 0xFFFFFF;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	mlx_put_image_to_window(info->mlx, info->win, mini, 0, 0);
// }
#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 720
#define HEIGHT 480
#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17
typedef struct s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void *mlx;
	void *win;
	double moveSpeed;
	double rotSpeed;
} t_info;

int worldMap[24][24] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int key_press(int key, t_info *info)
{
	if (key == K_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	// move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (key == K_A)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirY * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirX * info->moveSpeed;
	}
	if (key == K_D)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirY * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirX * info->moveSpeed;
	}
	// rotate to the right
	if (key == K_AR_R)
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	// rotate to the left
	if (key == K_AR_L)
	{
		// both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

void verLine(t_info *info, int x, int y1, int y2, int color)
{
	int y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}

void calc(t_info *info)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		// camera X ->  -1(left) ~~ 0(mid) ~~ 1(right)
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;

		// current ray location
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;	 // was a NS or a EW wall hit?

		// calculate step and initial sideDist
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

		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
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
			// Check if ray has hit a wall
			if (worldMap[mapY][mapX] > 0)
				hit = 1;
		}
		if (side == 0)
			perWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

#ifdef DEBUG
		printf("side = %d\n", side);
		printf("perwalldist %f\n", perWallDist);
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
#endif
		int color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;

		if (side == 1)
			color = color / 2;

		verLine(info, x, drawStart, drawEnd, color);

		x++;
	}
#ifdef DEBUG
// exit(0);
#endif
}

void back_ground(t_info *info)
{
	int color;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (y < HEIGHT / 2)
				color = 0xFFFFFF;
			else
				color = 0x000001;
			mlx_pixel_put(info->mlx, info->win, x, y, color);
		}
	}
}

int	idx = 0;

int main_loop(t_info *info)
{
	mlx_clear_window(info->mlx, info->win);
	back_ground(info);
	calc(info);
	// mini_map(info);
	printf("%d renderd\n", ++idx);
	return (0);
}

int main()
{
	t_info info;

	info.mlx = mlx_init();

	// 위치와 방향 벡터는 플레이어의 움직임과 시야를 제어하는 데 사용되며,
	// 평면 벡터는 시야의 너비를 조정합니다.

	// player location pos(x, y) 플레이어 위치 벡터
	info.posX = 22;
	info.posY = 12;

	// player direction(x, y) 플레이어 방향 벡터
	info.dirX = -1;
	info.dirY = 0;

	// camera line 카메라 평면벡터
	info.planeX = 0;
	info.planeY = 0.66;

	info.moveSpeed = 0.2;
	info.rotSpeed = 0.2;

	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "01_prac");
	mlx_loop_hook(info.mlx, main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, key_press, &info);
	mlx_loop(info.mlx);
}