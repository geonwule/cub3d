/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:15:17 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:18:45 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_vars *vars)
{
	write(1, "Player has exited the game\n", 27);
	mlx_destroy_window(vars->mlx, vars->win);
	free_map(&vars->map);
	free_vars(vars);
	exit(EXIT_SUCCESS);
}
