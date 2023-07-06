/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_function1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 04:28:40 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/07 02:26:58 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	attack(t_vars *vars)
{
	int		x;
	int		y;
	void	*shot;
	void	*shot2;

	vars->data.hand_change = 1;
	shot = ft_xpm_file_to_image(vars->mlx, "texture/etc/clo_1.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, shot, WIN_WIDTH / 12 * 5, \
			WIN_HEIGHT / 3);
	shot2 = ft_xpm_file_to_image(vars->mlx, "texture/etc/clo_2.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, shot2, WIN_WIDTH / 12 * 5, \
			WIN_HEIGHT / 3);
	kill_monster(vars, &vars->info, vars->map.arr);
}

void	reset_game(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	map = vars->map.arr;
	free_vars(vars);
	init_vars(vars);
	init_vars_info(vars);
	i = -1;
	while (++i < vars->map.height)
	{
		j = -1;
		while (++j < vars->map.width)
		{
			if (map[i][j] == 'b')
				map[i][j] = 'B';
			else if (map[i][j] == 'M' || map[i][j] == 'P')
				map[i][j] = '0';
		}
	}
}
