/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:23:47 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/06 11:34:30 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_mini_back(t_vars *vars)
{
	void	*mini_back;

	mini_back = mlx_new_image(vars->mlx, vars->map.width * 10, \
				vars->map.height * 10);
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
}

static void	put_mini_xpm(t_vars *vars, char **map, int x, int y)
{
	if (x == (int)vars->info.pos_x && y == (int)vars->info.pos_y)
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.player_x, y * 10, x * 10);
	else if (map[x][y] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.wall_x, y * 10, x * 10);
	else if (map[x][y] == 'M')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.monster_x, y * 10, x * 10);
	else if (map[x][y] == 'B')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.door_x, y * 10, x * 10);
	else if (map[x][y] == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.potion_x, y * 10, x * 10);
	else if (map[x][y] == 'H')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.npc_x, y * 10, x * 10);
	else if (map[x][y] == '0' || map[x][y] == 'b')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.empty_x, y * 10, x * 10);
}

static void	put_player_dir_xpm(t_vars *vars)
{
	int	x;
	int	y;

	x = (int)vars->info.pos_x;
	y = (int)vars->info.pos_y;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mini.dir_x, \
			y * 10 + vars->info.dir_y * 7, x * 10 + vars->info.dir_x * 7);
}

static void	fill_minimap(t_vars *vars, char **map)
{
	int	x;
	int	y;

	x = 0;
	while (x < vars->map.height)
	{
		y = 0;
		while (y < vars->map.width)
		{
			put_mini_xpm(vars, map, x, y);
			y++;
		}
		x++;
	}
	put_player_dir_xpm(vars);
}

void	mini_map(t_vars *vars)
{
	char	**map;

	map = vars->map.arr;
	fill_mini_back(vars);
	fill_minimap(vars, map);
}
