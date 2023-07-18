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

static void	put_player_dir_xpm(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->mini.pos[X];
	y = vars->mini.pos[Y];
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mini.dir_x, \
			y * 10 + vars->info.dir_y * 7, x * 10 + vars->info.dir_x * 7);
}

static int	init_fact_location(t_vars *vars, int flag)
{
	int location;

	if (flag == X)
		location = (int)vars->info.pos_x - vars->mini.len[X] / 2;
	else
		location = (int)vars->info.pos_y - vars->mini.len[Y] / 2;
	if (location < 0)
		location = 0;
	return (location);
}

static void	fill_minimap(t_vars *vars, char **map)
{
	int	x;
	int	y;
	int	loc[2];

	x = 0;
	loc[X] = init_fact_location(vars, X);
	while (x < vars->mini.len[X])
	{
		y = 0;
		loc[Y] = init_fact_location(vars, Y);
		while (y < vars->mini.len[Y])
		{
			if (loc[X] >= vars->map.height || loc[Y] >= vars->map.width)
				put_mini_xpm(vars, map, x, y, loc[X], loc[Y], 1);
			else
				put_mini_xpm(vars, map, x, y, loc[X], loc[Y], 0);
			if (loc[X] == (int)vars->info.pos_x && loc[Y] == (int)vars->info.pos_y)
			{
				vars->mini.pos[X] = x;
				vars->mini.pos[Y] = y;
			}
			y++;
			loc[Y]++;
		}
		x++;
		loc[X]++;
	}
	put_player_dir_xpm(vars);
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
