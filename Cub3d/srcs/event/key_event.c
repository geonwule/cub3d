/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:14:28 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/27 13:21:17 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int keycode, t_vars *vars)
{
	#ifdef KEY_DEBUG
	if (keycode == W)
        printf("release W\n");
	else if (keycode == A)
        printf("release A\n");
	else if (keycode == S)
        printf("release S\n");
	else if (keycode == D)
        printf("release D\n");
	#endif
	if (keycode >= 0 && keycode <= 255)
		vars->keyboard[keycode] = 0;
	return (0);
}
int is_weak_brick(t_vars *vars, int x, int y)
{
	char	spot;

	spot = vars->map.arr[x][y];
	if (spot == 'B' || spot == 'b' || spot == 'H')
		return (1);
	return (0);
}

void	monster_kill(t_vars *vars)
{
	char	**map = vars->map.arr;
	t_info	*info = vars->info;
	double	cameraX = 0;
	double	rayDirX = info->dirX + info->planeX * cameraX;
	double	rayDirY = info->dirY + info->planeY * cameraX;

	int	mapX = (int)info->posX;
	int	mapY = (int)info->posY;

	double	sideDistX;
	double	sideDistY;

	double	deltaDistX = fabs(1 / rayDirX);
	double	deltaDistY = fabs(1 / rayDirY);
	
	int	stepX;
	int	stepY;

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
	
	int hit = 0;
	while (1)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
		}
		if (map[mapX][mapY] == '0' || map[mapX][mapY] == 'b' \
			|| map[mapX][mapY] == 'P')
			continue;
		if (map[mapX][mapY] == 'M')
		{
			hit = 1;
			break ;
		}
		else
			break ;
	}
	if (hit)
	{
		if (random_generator(3))
			map[mapX][mapY] = 'P';
		else
			map[mapX][mapY] = '0';
		vars->hunt++;
		vars->m_num--;
		vars->monster_come = 0;
		if (vars->quest_num && vars->quest_monster_num > 0)
			vars->quest_monster_num--;
	}
}

void	reset_game(t_vars *vars)
{
	char	**map = vars->map.arr;

	vars_free(vars);
	vars_allocation(vars);
	vars_init(vars);	
	for (int i = 0; i < vars->map.height; i++)
	{
		for (int j = 0; j < vars->map.width; j++)
		{
			if (map[i][j] == 'b')
				map[i][j] = 'B';
			else if (map[i][j] == 'M' || map[i][j] == 'P')
				map[i][j] = '0';
		}
	}
}

void	attack(t_vars *vars)
{
	int		x;
	int		y;
	void	*shot;
	void	*shot2;

	vars->gun_change = 1;
	shot = ft_xpm_file_to_image(vars->mlx, "texture/etc/clo_1.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, shot, WIN_WIDTH / 12 * 5, WIN_HEIGHT / 3);
	shot2 = ft_xpm_file_to_image(vars->mlx, "texture/etc/clo_2.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, shot2, WIN_WIDTH / 12 * 5, WIN_HEIGHT / 3);
	monster_kill(vars);
}

void	return_ellinia(t_vars *vars)
{
	t_info	*info;

	info = vars->info;
	info->posX = vars->init_pos[X];
	info->posY = vars->init_pos[Y];
	info->dirX = vars->init_dir[X];
	info->dirY = vars->init_dir[Y];
	info->planeX = vars->init_plane[X];
	info->planeY = vars->init_plane[Y];
}

void	open_door_tell_npc(t_vars *vars, char **map)
{
	t_info		*info;
	double		tmp[2];
	const int	dx[4] = {-1, 1, 0, 0};
	const int	dy[4] = {0, 0, -1, 1};
	info = vars->info;
	for (int i = 0; i < 4; i++)
	{
		tmp[X] = info->posX + dx[i];
		tmp[Y] = info->posY + dy[i]; 
		if (tmp[X] < 0 || tmp[X] >= WIN_HEIGHT \
			|| tmp[Y] < 0 || tmp[Y] >= WIN_WIDTH \
			|| !is_weak_brick(vars, (int)tmp[X], (int)tmp[Y]))
			continue ;
		if (map[(int)tmp[X]][(int)tmp[Y]] == 'B')
			map[(int)tmp[X]][(int)tmp[Y]] = 'b';
		else if (map[(int)tmp[X]][(int)tmp[Y]] == 'b')
			map[(int)tmp[X]][(int)tmp[Y]] = 'B';
		else if (map[(int)tmp[X]][(int)tmp[Y]] == 'H')
			vars->npc_talk = 1;
	}
}

void	adjust_gamespeed(t_info *info, int keycode)
{
	if(keycode == N)
	{
		info->moveSpeed -= 0.01;
		info->rotSpeed -= 0.01;
	}
	else if (keycode == M)
	{
		info->moveSpeed += 0.01;
		info->rotSpeed += 0.01;
	}
}

void	turn_back(t_info *info)
{
	info->dirX *= -1;
	info->dirY *= -1;
	info->planeX *= -1;
	info->planeY *= -1;
}

int	key_press(int keycode, t_vars *vars)
{
	#ifdef KEY_DEBUG
	if (keycode == W)
        printf("press W\n");
	else if (keycode == A)
        printf("press A\n");
	else if (keycode == S)
        printf("press S\n");
	else if (keycode == D)
        printf("press D\n");
	else if (keycode == ESC)
		printf("press ESC\n");
	#endif

	t_info	*info;
	char	**map;

	info = vars->info;
	map = vars->map.arr;
	if (keycode == P)
		reset_game(vars);
	if (vars->npc_talk)
		return (0);
	if (keycode >= 0 && keycode <= 255)
		vars->keyboard[keycode] = 1;
	if (keycode == N || keycode == M)
		adjust_gamespeed(info, keycode);
	if (keycode == SPACE)
		attack(vars);
	if (keycode == Q)
		turn_back(info);
	if (keycode == B)
		open_door_tell_npc(vars, map);
	if (keycode == R)
		return_ellinia(vars);
	return (0);
}