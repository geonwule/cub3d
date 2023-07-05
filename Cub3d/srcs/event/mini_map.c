/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:23:47 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/05 11:55:53 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_minimap_put_mlx(t_vars *vars, char **map, int x, int y)
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

static void	minimap_put_mlx(t_vars *vars, char **map, \
								int mini_height, int mini_width)
{
	int	x;
	int	y;

	x = 0;
	while (x < mini_height)
	{
		y = 0;
		while (y < mini_width)
		{
			process_minimap_put_mlx(vars, map, x, y);
			y++;
		}
		x++;
	}
	x = (int)vars->info.pos_x;
	y = (int)vars->info.pos_y;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mini.dir_x, \
			y * 10 + vars->info.dir_y * 7, x * 10 + vars->info.dir_x * 7);
}

void	mini_map(t_vars *vars)
{
	char	**map;
	void	*mini_back;
	int		i;
	int		j;

	map = vars->map.arr;
	mini_back = mlx_new_image(vars->mlx, vars->map.width * 10, \
				vars->map.height * 10);
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			mlx_pixel_put(vars->mlx, mini_back, j, i, 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
	minimap_put_mlx(vars, map, vars->map.height, vars->map.width);
}
