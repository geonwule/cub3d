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

int is_weak_brick(t_vars *vars, int x, int y)
{
	char	spot;

	spot = vars->map.arr[x][y];
	if (spot == 'B' || spot == 'b' || spot == 'H')
		return (1);
	return (0);
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