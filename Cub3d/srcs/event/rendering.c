/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:17:00 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 05:10:22 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (x == (int)vars->info->posX && y == (int)vars->info->posY)
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
			y++;
		}
		x++;
	}
	x = (int)vars->info->posX;
	y = (int)vars->info->posY;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mini.dir_x, \
			y * 10 + vars->info->dirY * 7, x * 10 + vars->info->dirX * 7);
}

static void	mini_map(t_vars *vars)
{
	int		mini_width;
	int		mini_height;
	char	**map;
	void	*mini_back;

	mini_width = vars->map.width;
	mini_height = vars->map.height;
	map = vars->map.arr;
	mini_back = mlx_new_image(vars->mlx, mini_width * 10, mini_height * 10);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
			mlx_pixel_put(vars->mlx, mini_back, y, x, 0);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
	minimap_put_mlx(vars, map, mini_height, mini_width);
}

static void	draw_mlx(t_vars *vars)
{
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			vars->info->img.data[y * WIN_WIDTH + x] = vars->info->buf[y][x];
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->info->img.img, 0, 0);
}

static int	dead_check_game_end(t_vars *vars)
{
	if (!vars->data.dead_check)
		return (0);
	if (vars->data.dead_check)
	{
		if (vars->data.keyboard[ESC])
			exit_game(vars);
		else if (vars->data.keyboard[P])
		{
			reset_game(vars);
			vars->data.dead_check = 0;
			return (0);
		}
	}
	return (1);
}

int	rendering(t_vars *vars)
{
	if (dead_check_game_end(vars))
		return (0);
	manage_monster(vars);
	check_key_and_mouse(vars);
	mlx_clear_window(vars->mlx, vars->win);
	fill_background(vars, vars->map.info.c, vars->map.info.f);
	ray_casting(vars, vars->info, vars->map.arr);
	sprite(vars);
	draw_mlx(vars);
	print_window1(vars);
	print_window2(vars);
	mini_map(vars);
	if (vars->data.dead_check)
		mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->xpm.dead, WIN_WIDTH / 100 * 33, WIN_HEIGHT / 100 * 30);
	return (0);
}
