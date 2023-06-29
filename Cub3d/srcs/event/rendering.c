/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:17:00 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/27 16:18:00 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void mini_map(t_vars *vars)
{
	int mini_width, mini_height;
	char	**map = vars->map.arr;

	mini_width = vars->map.width;
	mini_height = vars->map.height;
	
	void	*mini_back = mlx_new_image(vars->mlx, mini_width * 10, mini_height * 10);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
		{
			mlx_pixel_put(vars->mlx, mini_back, y, x, 0);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
		{
			if (x == (int)vars->info->posX && y == (int)vars->info->posY)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player_x, y * 10, x * 10);
			else if (map[x][y] == '1')// wall
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'M')// monster
				mlx_put_image_to_window(vars->mlx, vars->win, vars->monster_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'B')// break 벽
				mlx_put_image_to_window(vars->mlx, vars->win, vars->door_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'P')// break 벽
				mlx_put_image_to_window(vars->mlx, vars->win, vars->potion_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'H')// npc
				mlx_put_image_to_window(vars->mlx, vars->win, vars->npc_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == '0' || map[x][y] == 'b')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->empty_x, y * 10, x * 10);
		}
	}
	int x = (int)vars->info->posX;
	int y = (int)vars->info->posY;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->dir_x, y * 10 + vars->info->dirY * 7, x * 10 + vars->info->dirX * 7); //dir
}

void	draw_mlx(t_vars *vars)
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

int	dead_check_game_end(t_vars *vars)
{
	if (!vars->dead_check)
		return (0);
	if (vars->dead_check)
	{
		if (vars->keyboard[ESC])
			exit_game(vars);
		else if (vars->keyboard[P])
		{
			reset_game(vars);
			vars->dead_check = 0;
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

	mlx_clear_window(vars->mlx, vars->win); // clear window
	fill_background(vars, vars->map.info.c, vars->map.info.f); // study_need // fill back ground
	map_set(vars);
	draw_mlx(vars);

	print_window1(vars);
	print_window2(vars);

	mini_map(vars);	
	if (vars->dead_check)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->dead, WIN_WIDTH / 100 * 33, WIN_HEIGHT / 100 * 30);
	return (0);
}
