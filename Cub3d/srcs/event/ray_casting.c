/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:18:48 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/05 11:50:53 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_vars *vars, t_info *info, char **map)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(info, &ray, x);
		check_ray_dir(info, &ray);
		dda(vars, map, &ray);
		check_ray_texture(info, &ray, map);
		apply_texture(info, &ray, x, ray.draw_start);
		info->z_buffer[x] = ray.perwalldist;
		x++;
	}
}
