/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_function2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 04:31:12 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 04:33:16 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_gamespeed(t_info *info, int keycode)
{
	if (keycode == N)
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

static int	is_door_or_npc(t_vars *vars, int x, int y)
{
	char	spot;

	spot = vars->map.arr[x][y];
	if (spot == 'B' || spot == 'b' || spot == 'H')
		return (1);
	return (0);
}

void	open_door_tell_npc(t_vars *vars, char **map)
{
	t_info		*info;
	double		tmp[2];
	const int	dx[4] = {-1, 1, 0, 0};
	const int	dy[4] = {0, 0, -1, 1};
	int			i;

	info = vars->info;
	i = -1;
	while (++i < 4)
	{
		tmp[X] = info->posX + dx[i];
		tmp[Y] = info->posY + dy[i];
		if (tmp[X] < 0 || tmp[X] >= WIN_HEIGHT \
			|| tmp[Y] < 0 || tmp[Y] >= WIN_WIDTH \
			|| !is_door_or_npc(vars, (int)tmp[X], (int)tmp[Y]))
			continue ;
		if (map[(int)tmp[X]][(int)tmp[Y]] == 'B')
			map[(int)tmp[X]][(int)tmp[Y]] = 'b';
		else if (map[(int)tmp[X]][(int)tmp[Y]] == 'b')
			map[(int)tmp[X]][(int)tmp[Y]] = 'B';
		else if (map[(int)tmp[X]][(int)tmp[Y]] == 'H')
			vars->data.npc_talk = 1;
	}
}

void	return_ellinia(t_vars *vars)
{
	t_info	*info;

	info = vars->info;
	info->posX = vars->data.init_pos[X];
	info->posY = vars->data.init_pos[Y];
	info->dirX = vars->data.init_dir[X];
	info->dirY = vars->data.init_dir[Y];
	info->planeX = vars->data.init_plane[X];
	info->planeY = vars->data.init_plane[Y];
}
