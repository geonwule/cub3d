/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_monster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 04:35:32 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:48:58 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	monster_rezen(t_vars *vars)
{
	int		i;
	int		j;
	char	**map;

	map = vars->map.arr;
	if (vars->data.m_num || vars->data.warning_time < 50)
		return ;
	vars->data.warning_time = 0;
	i = -1;
	while (++i < vars->map.height)
	{
		j = -1;
		while (++j < vars->map.width)
		{
			if (i > vars->map.height * 0.8 && vars->map.width * 0.7)
				break ;
			if (map[i][j] == '0' && random_generator(2) \
				&& i != (int)vars->info.pos_x && j != (int)vars->info.pos_y)
			{
				map[i][j] = 'M';
				vars->data.m_num++;
				usleep(1);
			}
		}
	}
}

static void	monster_move(t_vars *vars, int x_or_y, int step)
{
	char	**map;
	int		x;
	int		y;

	x = vars->data.m_pos[X];
	y = vars->data.m_pos[Y];
	map = vars->map.arr;
	map[x][y] = '0';
	if (x_or_y == X)
	{
		map[x + step][y] = 'M';
		vars->data.m_pos[X] += step;
	}
	else
	{
		map[x][y + step] = 'M';
		vars->data.m_pos[Y] += step;
	}
}

static void	move_x(t_vars *vars, t_info *info, char **map)
{
	int	x;
	int	y;

	x = vars->data.m_pos[X];
	y = vars->data.m_pos[Y];
	if ((int)info->pos_x < x && map[x - 1][y] == '0')
	{
		if (((int)info->pos_x == x - 1 && (int)info->pos_y == y) \
				&& vars->data.hp > 0)
			vars->data.hp -= 1;
		else
			monster_move(vars, X, -1);
	}
	else if ((int)info->pos_x > x && map[x + 1][y] == '0')
	{
		if (((int)info->pos_x == x + 1 && (int)info->pos_y == y))
			vars->data.hp -= 1;
		else
			monster_move(vars, X, 1);
	}
}

static void	move_y(t_vars *vars, t_info *info, char **map)
{
	int	x;
	int	y;

	x = vars->data.m_pos[X];
	y = vars->data.m_pos[Y];
	if ((int)info->pos_y < y && map[x][y - 1] == '0')
	{
		if ((int)info->pos_x == x && (int)info->pos_y == y - 1)
			vars->data.hp -= 1;
		else
			monster_move(vars, Y, -1);
	}
	else if ((int)info->pos_y > y && map[x][y + 1] == '0')
	{
		if ((int)info->pos_x == x && (int)info->pos_y == y + 1)
			vars->data.hp -= 1;
		else
			monster_move(vars, Y, 1);
	}
}

void	manage_monster(t_vars *vars)
{
	t_info	*info;
	char	**map;

	info = &vars->info;
	map = vars->map.arr;
	monster_rezen(vars);
	if (!vars->data.monster_come || ++vars->data.m_speed % 30 != 0 \
		|| map[vars->data.m_pos[X]][vars->data.m_pos[Y]] != 'M' \
		|| vars->data.npc_talk)
		return ;
	move_x(vars, info, map);
	move_y(vars, info, map);
}
