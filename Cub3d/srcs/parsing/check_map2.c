/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:40:10 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/03 22:41:26 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir_plane_ns(t_vars *vars, char type)
{
	if (type == 'N')
	{
		vars->info->dirX = -1.0;
		vars->info->dirY = 0.0;
		vars->info->planeX = 0.0;
		vars->info->planeY = 0.66;
	}
	else if (type == 'S')
	{
		vars->info->dirX = 1.0;
		vars->info->dirY = 0.0;
		vars->info->planeX = 0.0;
		vars->info->planeY = -0.66;
	}
}

void	init_dir_plane_ew(t_vars *vars, char type)
{
	if (type == 'E')
	{
		vars->info->dirX = 0.0;
		vars->info->dirY = 1.0;
		vars->info->planeX = 0.66;
		vars->info->planeY = 0.0;
	}
	else if (type == 'W')
	{
		vars->info->dirX = 0.0;
		vars->info->dirY = -1.0;
		vars->info->planeX = -0.66;
		vars->info->planeY = 0.0;
	}
}
