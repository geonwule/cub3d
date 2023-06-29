/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:35:03 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/28 04:24:18 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_plyer_and_is_valid(char **map, t_vars *vars)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("NWES01HB ", map[i][j]))
				return (-1);
			if (ft_strchr("NWES", map[i][j]))
			{
				vars->info->posX = i;
				vars->info->posY = j;
				if (map[i][j] == 'N')
				{
					vars->info->dirX = -1.0;
					vars->info->dirY = 0.0;
					vars->info->planeX = 0.0;
					vars->info->planeY = 0.66;
				}
				else if (map[i][j] == 'S')
				{
					vars->info->dirX = 1.0;
					vars->info->dirY = 0.0;
					vars->info->planeX = 0.0;
					vars->info->planeY = -0.66;
				}
				else if (map[i][j] == 'E')
				{
					vars->info->dirX = 0.0;
					vars->info->dirY = 1.0;
					vars->info->planeX = 0.66;
					vars->info->planeY = 0.0;
				}
				else if (map[i][j] == 'W')
				{
					vars->info->dirX = 0.0;
					vars->info->dirY = -1.0;
					vars->info->planeX = -0.66;
					vars->info->planeY = 0.0;
				}
				map[i][j] = '0';
				cnt++;
			}
			j++;
		}
		i++;
	}
	return (cnt);
}

static int	check_edge(int i, int j, t_vars *vars)
{
	char	**map;

	map = vars->map.arr;
	if ((i == 0 || i == (vars->map.height - 1) \
		|| j == 0 || j == (vars->map.width - 1)) \
		&& (map[i][j] != ' ' && map[i][j] != '1'))
		return (1);
	return (0);
}

static int	check_dir(int i, int j, t_vars *vars)
{
	int			nx;
	int			ny;
	const int	dx[4] = {0, 1, 0, -1};
	const int	dy[4] = {1, 0, -1, 0};
	int			k;

	k = 0;
	while (k < 4)
	{
		nx = i + dx[k];
		ny = j + dy[k];
		if (nx < 0 || nx >= vars->map.height || ny < 0 || ny >= vars->map.width)
		{
			k++;
			continue ;
		}
		if (vars->map.arr[nx][ny] == ' ' \
			&& (vars->map.arr[i][j] != '1' && vars->map.arr[i][j] != ' '))
			return (1);
		k++;
	}
	return (0);
}

int	check_map(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	map = vars->map.arr;
	if (count_plyer_and_is_valid(map, vars) != 1)
	{
		printf("player is not one or invalid map\n");	// del
		return (1);
	}
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_edge(i, j, vars))
			{
				printf("[%d][%d] is not wall\n", i, j); // del
				return (1);
			}
			if (check_dir(i, j, vars))
			{
				printf("[%d][%d] is not wall2\n", i, j); // del
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
