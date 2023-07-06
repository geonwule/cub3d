/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:26:13 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/07 02:26:33 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_m(t_info *info, t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir[X] = info->dir_x + info->plane_x * ray->camera_x;
	ray->dir[Y] = info->dir_y + info->plane_y * ray->camera_x;
	ray->map[X] = (int)info->pos_x;
	ray->map[Y] = (int)info->pos_y;
	ray->delta_d[X] = fabs(1 / ray->dir[X]);
	ray->delta_d[Y] = fabs(1 / ray->dir[Y]);
	ray->hit = 0;
}

static void	check_ray_dir_m(t_info *info, t_ray *ray)
{
	if (ray->dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_d[X] = (info->pos_x - ray->map[X]) * ray->delta_d[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_d[X] = (ray->map[X] + 1.0 - info->pos_x) * ray->delta_d[X];
	}
	if (ray->dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_d[Y] = (info->pos_y - ray->map[Y]) * ray->delta_d[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_d[Y] = (ray->map[Y] + 1.0 - info->pos_y) * ray->delta_d[Y];
	}
}

static void	dda_m(char **map, t_ray *ray)
{
	while (1)
	{
		if (ray->side_d[X] < ray->side_d[Y])
		{
			ray->side_d[X] += ray->delta_d[X];
			ray->map[X] += ray->step[X];
		}
		else
		{
			ray->side_d[Y] += ray->delta_d[Y];
			ray->map[Y] += ray->step[Y];
		}
		if (map[ray->map[X]][ray->map[Y]] == '0' \
			|| map[ray->map[X]][ray->map[Y]] == 'b' \
			|| map[ray->map[X]][ray->map[Y]] == 'P')
			continue ;
		if (map[ray->map[X]][ray->map[Y]] == 'M')
		{
			ray->hit = 1;
			break ;
		}
		else
			break ;
	}
}

static void	drop_item(t_vars *vars, char **map, t_ray *ray)
{
	if (random_generator(3))
		map[ray->map[X]][ray->map[Y]] = 'P';
	else
		map[ray->map[X]][ray->map[Y]] = '0';
	vars->data.hunt++;
	vars->data.m_num--;
	vars->data.monster_come = 0;
	if (vars->data.quest_num && vars->data.quest_monster_num > 0)
		vars->data.quest_monster_num--;
}

void	kill_monster(t_vars *vars, t_info *info, char **map)
{
	t_ray	ray;

	init_ray_m(info, &ray);
	check_ray_dir_m(info, &ray);
	dda_m(map, &ray);
	if (ray.hit)
		drop_item(vars, map, &ray);
}
