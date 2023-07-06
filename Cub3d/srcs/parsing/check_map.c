/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:35:03 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/06 15:20:36 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_info(t_vars *vars, char **map, int i, int j)
{
	if (map[i][j] == 'N')
		init_dir_plane_ns(vars, 'N');
	else if (map[i][j] == 'S')
		init_dir_plane_ns(vars, 'S');
	else if (map[i][j] == 'E')
		init_dir_plane_ew(vars, 'E');
	else if (map[i][j] == 'W')
		init_dir_plane_ew(vars, 'W');
}

static int	count_plyer_and_is_valid(char **map, t_vars *vars)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr("NWES01HB \n", map[i][j]))
				return (-1);
			if (ft_strchr("NWES", map[i][j]))
			{
				vars->data.init_pos[X] = i + 0.1;
				vars->data.init_pos[Y] = j + 0.1;
				init_player_info(vars, map, i, j);
				map[i][j] = '0';
				cnt++;
			}
		}
	}
	return (cnt);
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
		if ((vars->map.arr[i][j] != '1' && vars->map.arr[i][j] != ' ') \
			&& vars->map.arr[nx][ny] == ' ')
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
		return (RETURN_FAILURE);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_dir(i, j, vars))
				return (RETURN_FAILURE);
			j++;
		}
		i++;
	}
	return (RETURN_SUCCESS);
}
