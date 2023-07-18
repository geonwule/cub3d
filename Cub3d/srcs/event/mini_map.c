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

	mini_back = mlx_new_image(vars->mlx, MINI_WIDTH, MINI_HEIGHT);
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
}

static void	put_mini_xpm(t_vars *vars, char **map, int x, int y, int px, int py, int empty)
{
	if (empty)
		return ;
	if (px == (int)vars->info.pos_x && py == (int)vars->info.pos_y)
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.player_x, y * 10, x * 10);
	else if (map[px][py] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.wall_x, y * 10, x * 10);
	else if (map[px][py] == 'M')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.monster_x, y * 10, x * 10);
	else if (map[px][py] == 'B')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.door_x, y * 10, x * 10);
	else if (map[px][py] == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.potion_x, y * 10, x * 10);
	else if (map[px][py] == 'H')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.npc_x, y * 10, x * 10);
	else if (map[px][py] == '0' || map[px][py] == 'b')
		mlx_put_image_to_window(vars->mlx, vars->win, \
					vars->mini.empty_x, y * 10, x * 10);
}

static void	put_player_dir_xpm(t_vars *vars, int px, int py)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mini.dir_x, \
			py * 10 + vars->info.dir_y * 7, px * 10 + vars->info.dir_x * 7);
}

static void	fill_minimap(t_vars *vars, char **map)
{
	int	min[2];

	min[X] = MINI_HEIGHT / 10;
	min[Y] = MINI_WIDTH / 10;

	int	pos[2];
	int	x;
	int	y;
	int	pr[2];
	x = 0;
	pr[X] = (int)vars->info.pos_x - min[X] / 2;
	if (pr[X] < 0)
		pr[X] = 0;
	while (x < min[X])
	{
		y = 0;
		pr[Y] = (int)vars->info.pos_y - min[Y] / 2;
		if (pr[Y] < 0)
			pr[Y] = 0;
		while (y < min[Y])
		{
			if (pr[X] >= vars->map.height || pr[Y] >= vars->map.width)
				put_mini_xpm(vars, map, x, y, pr[X], pr[Y], 1);
			else
				put_mini_xpm(vars, map, x, y, pr[X], pr[Y], 0);
			if (pr[X] == (int)vars->info.pos_x && pr[Y] == (int)vars->info.pos_y)
			{
				pos[X] = x;
				pos[Y] = y;
			}
			y++;
			pr[Y]++;
		}
		x++;
		pr[X]++;
	}
	put_player_dir_xpm(vars, pos[X], pos[Y]);
}

void	mini_map(t_vars *vars)
{
	char	**map;

	map = vars->map.arr;
	if (vars->data.mini_expan)
	{
		fill_mini_back_expan(vars);
		fill_minimap_expan(vars, map);
		return ;
	}
	fill_mini_back(vars);
	fill_minimap(vars, map);
}
