/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:17:00 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/20 17:41:34 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern char	map[15][34]; //tmp

int	can_move(t_vars *vars, int x, int y)
{
	char	spot;

	spot = map[x][y];
	if (spot == '0' || spot == 'N' || spot == 'S' \
		|| spot == 'W' || spot == 'E' || spot == 'b')
	{
		// printf("can move\n");//tmp
		return (1);
	}
	//tmp
	// printf("init x = %d y = %d\n", (int)vars->info->posX, (int)vars->info->posY);
	// printf("x = %d, y = %d\n", x, y);
	// printf("%c\n", map[x][y]);
	// printf("can not move\n");
	return (0);
}

static void	key_check(t_vars *vars)
{
	t_info	*info = vars->info;
	
	if (vars->keyboard[ESC])
       	exit_game(vars);
	if (vars->keyboard[W])
	{
		if (can_move(vars, (int)(info->posX + info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			{
				info->posX += info->dirX * info->moveSpeed;
			}
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY + info->dirY * info->moveSpeed)))
			info->posY += info->dirY * info->moveSpeed;
			//printf("posX = %d, dirX = %d, posY = %d, dirY = %d\n", (int)info->posX, (int)info->dirX, (int)info->posY, (int)info->dirY);
	}
	if (vars->keyboard[S])
	{
		if (can_move(vars, (int)(info->posX - info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX -= info->dirX * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY - info->dirY * info->moveSpeed)))
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (vars->keyboard[D])
	{
		if (can_move(vars, (int)(info->posX + info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX += info->dirY * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY - info->dirX * info->moveSpeed)))
			info->posY -= info->dirX * info->moveSpeed;
	}
	if (vars->keyboard[A])
	{
		if (can_move(vars, (int)(info->posX - info->dirY * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX -= info->dirY * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY + info->dirX * info->moveSpeed)))
			info->posY += info->dirX * info->moveSpeed;
	}
	if (vars->keyboard[LEFT])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (vars->keyboard[RIGHT])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
}

static void mini_map(t_vars *vars)
{
	int mini_width, mini_height;

	mini_width = 34;
	mini_height = 15;
	
	void	*mini_back = mlx_new_image(vars->mlx, mini_width * 10, mini_height * 10);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
		{
			mlx_pixel_put(vars->mlx, mini_back, y, x, 0);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
		{
			if (x == (int)vars->info->posX && y == (int)vars->info->posY)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player_x, y * 10, x * 10);
			else if (map[x][y] == '1')// wall
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'M')// monster
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'B')// break 벽
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == '0' || map[x][y] == 'b')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->empty_x, y * 10, x * 10);
		}
	}
}


void	draw_mlx(t_vars *vars)
{
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			vars->info->img.data[y * WIN_WIDTH + x] = vars->info->buf[y][x];
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->info->img.img, 0, 0);
}

// int idx = 0;
// 	printf("render %d ok\n", ++idx);

void	aim_point(t_vars *vars)
{
	int x, y;
	void	*aim = mlx_xpm_file_to_image(vars->mlx, "texture/aim.xpm", &x, &y);
	void	*gun = mlx_xpm_file_to_image(vars->mlx, "texture/gun.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, aim, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_put_image_to_window(vars->mlx, vars->win, gun, WIN_WIDTH / 9 * 5, WIN_HEIGHT / 9 * 7);
}

void	monster_come_on(t_vars *vars, int x, int y)
{
	t_info	*info = vars->info;
	
	// printf("vars->m_pos[y] - 1 %d\n",vars->m_pos[Y] - 1);
	// printf("map[x][vars->m_pos[y] - 1] = %c\n",  map[x][vars->m_pos[Y] - 1]);
	// printf("vars->m_pos[y] + 1 %d\n",vars->m_pos[Y] + 1);
	// printf("map[x][vars->m_pos[y] + 1] = %c\n",  map[x][vars->m_pos[Y] + 1]);
	if (info->posX < x && map[x - 1][y] == '0')
	{
		map[x][y] = '0';
		map[x - 1][y] = 'M';
		vars->m_pos[X] -= 1;
	}
	else if (map[x + 1][y] == '0')
	{
		map[x][y] = '0';
		map[x + 1][y] = 'M';
		vars->m_pos[X] += 1;
	}
	x = vars->m_pos[X];
	if (info->posY < y && map[x][y - 1] == '0')
	{
		map[x][y] = '0';
		map[x][y - 1] = 'M';
		vars->m_pos[Y] -= 1;
	}
	else if (map[x][y + 1] == '0')
	{
		map[x][y] = '0';
		map[x][y + 1] = 'M';
		vars->m_pos[Y] += 1;
	}
}

int i = 0;
int	rendering(t_vars *vars)
{
	if (vars->monster_come && ++i % 30 == 0)
	{
		if (map[vars->m_pos[X]][vars->m_pos[Y]] != 'M')
		{
			vars->monster_come = 0;
		}
		else
		{
			monster_come_on(vars, vars->m_pos[X], vars->m_pos[Y]);
		}
		printf("monster[%d][%d]\n", vars->m_pos[X], vars->m_pos[Y]);
	}
	key_check(vars);
	mlx_clear_window(vars->mlx, vars->win); // clear window
	fill_background(vars, vars->c, vars->f); // study_need // fill back ground
	map_set(vars);
	draw_mlx(vars);
	aim_point(vars);
	mini_map(vars);
	return (0);
}