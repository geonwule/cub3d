/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_function_dda.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:07:16 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 14:46:50 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_side_and_step(t_ray *ray)
{
	if (ray->side_d[X] < ray->side_d[Y])
	{
		ray->side_d[X] += ray->delta_d[X];
		ray->map[X] += ray->step[X];
		if (ray->step[X] < 0)
			ray->side = TEX_NO;
		else
			ray->side = TEX_SO;
	}
	else
	{
		ray->side_d[Y] += ray->delta_d[Y];
		ray->map[Y] += ray->step[Y];
		if (ray->step[Y] < 0)
			ray->side = TEX_EA;
		else
			ray->side = TEX_WE;
	}
}

static void	check_hit_and_monster(t_vars *vars, char **map, t_ray *ray)
{
	if (map[ray->map[X]][ray->map[Y]] == '1' \
			|| map[ray->map[X]][ray->map[Y]] == 'B')
		ray->hit = 1;
	if (map[ray->map[X]][ray->map[Y]] == 'M' && vars->data.monster_come == 0)
	{
		vars->data.m_pos[X] = ray->map[X];
		vars->data.m_pos[Y] = ray->map[Y];
		vars->data.monster_come = 1;
	}
}

void	dda(t_vars *vars, char **map, t_ray *ray)
{
	while (ray->hit == 0)
	{
		update_side_and_step(ray);
		check_hit_and_monster(vars, map, ray);
	}
}
