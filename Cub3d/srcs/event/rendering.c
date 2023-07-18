/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:17:00 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/17 12:25:34 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_mlx(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			vars->info.img.data[i * WIN_WIDTH + j] = vars->info.buf[i][j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->info.img.img, 0, 0);
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
	ray_casting(vars, &vars->info, vars->map.arr);
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
