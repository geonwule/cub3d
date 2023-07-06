/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:40:10 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/06 13:45:05 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir_plane_ns(t_vars *vars, char type)
{
	if (type == 'N')
	{
		vars->data.init_dir[X] = -1.0;
		vars->data.init_dir[Y] = 0.0;
		vars->data.init_plane[X] = 0.0;
		vars->data.init_plane[Y] = 0.66;
	}
	else if (type == 'S')
	{
		vars->data.init_dir[X] = 1.0;
		vars->data.init_dir[Y] = 0.0;
		vars->data.init_plane[X] = 0.0;
		vars->data.init_plane[Y] = -0.66;
	}
}

void	init_dir_plane_ew(t_vars *vars, char type)
{
	if (type == 'E')
	{
		vars->data.init_dir[X] = 0.0;
		vars->data.init_dir[Y] = 1.0;
		vars->data.init_plane[X] = 0.66;
		vars->data.init_plane[Y] = 0.0;
	}
	else if (type == 'W')
	{
		vars->data.init_dir[X] = 0.0;
		vars->data.init_dir[Y] = -1.0;
		vars->data.init_plane[X] = -0.66;
		vars->data.init_plane[Y] = 0.0;
	}
}
