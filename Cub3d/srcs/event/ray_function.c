/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 00:47:14 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 01:10:47 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_info *info, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir[X] = info->dirX + info->planeX * ray->camera_x;
	ray->dir[Y] = info->dirY + info->planeY * ray->camera_x;
	ray->map[X] = (int)info->posX;
	ray->map[Y] = (int)info->posY;
	ray->delta_d[X] = fabs(1 / ray->dir[X]);
	ray->delta_d[Y] = fabs(1 / ray->dir[Y]);
	ray->hit = 0;
}

void	check_ray_dir(t_info *info, t_ray *ray)
{
	if (ray->dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_d[X] = (info->posX - ray->map[X]) * ray->delta_d[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_d[X] = (ray->map[X] + 1.0 - info->posX) * ray->delta_d[X];
	}
	if (ray->dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_d[Y] = (info->posY - ray->map[Y]) * ray->delta_d[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_d[Y] = (ray->map[Y] + 1.0 - info->posY) * ray->delta_d[Y];
	}
}

void	check_ray_texture(t_info *info, t_ray *ray, char **map)
{
	if (ray->side <= 1)
		ray->perwalldist = (ray->map[X] - info->posX \
				+ (1 - ray->step[X]) / 2) / ray->dir[X];
	else
		ray->perwalldist = (ray->map[Y] - info->posY \
				+ (1 - ray->step[Y]) / 2) / ray->dir[Y];
	ray->line_height = (int)(WIN_HEIGHT / ray->perwalldist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (map[ray->map[X]][ray->map[Y]] == '1')
		ray->tex_num = ray->side;
	else if (map[ray->map[X]][ray->map[Y]] == 'B')
		ray->tex_num = TEX_DOOR;
	if (ray->side <= 1)
		ray->wall_x = info->posY + ray->perwalldist * ray->dir[Y];
	else
		ray->wall_x = info->posX + ray->perwalldist * ray->dir[X];
	ray->wall_x -= floor(ray->wall_x);
}

void	apply_texture(t_info *info, t_ray *ray, int x, int y)
{
	int	color;
	int	**texture;

	ray->tex[X] = (int)(ray->wall_x * (double)TEX_WIDTH);
	if (ray->side <= 1 && ray->dir[X] > 0)
		ray->tex[X] = TEX_WIDTH - ray->tex[X] - 1;
	if (ray->side >= 2 && ray->dir[Y] < 0)
		ray->tex[X] = TEX_WIDTH - ray->tex[X] - 1;
	ray->t_step = 1.0 * TEX_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 \
			+ ray->line_height / 2) * ray->t_step;
	color = ray->color;
	texture = info->texture;
	while (y < ray->draw_end)
	{
		ray->tex[Y] = (int)ray->tex_pos % (TEX_HEIGHT - 1);
		ray->tex_pos += ray->t_step;
		color = texture[ray->tex_num][TEX_HEIGHT * ray->tex[Y] + ray->tex[X]];
		info->buf[y][x] = color;
		y++;
	}
}
