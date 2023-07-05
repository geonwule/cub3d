/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:40:10 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:31:18 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir_plane_ns(t_vars *vars, char type)
{
	if (type == 'N')
	{
		vars->info.dir_x = -1.0;
		vars->info.dir_y = 0.0;
		vars->info.plane_x = 0.0;
		vars->info.plane_y = 0.66;
	}
	else if (type == 'S')
	{
		vars->info.dir_x = 1.0;
		vars->info.dir_y = 0.0;
		vars->info.plane_x = 0.0;
		vars->info.plane_y = -0.66;
	}
}

void	init_dir_plane_ew(t_vars *vars, char type)
{
	if (type == 'E')
	{
		vars->info.dir_x = 0.0;
		vars->info.dir_y = 1.0;
		vars->info.plane_x = 0.66;
		vars->info.plane_y = 0.0;
	}
	else if (type == 'W')
	{
		vars->info.dir_x = 0.0;
		vars->info.dir_y = -1.0;
		vars->info.plane_x = -0.66;
		vars->info.plane_y = 0.0;
	}
}
