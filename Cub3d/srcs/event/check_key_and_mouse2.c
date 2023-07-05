/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_and_mouse2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 04:11:57 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 20:47:11 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_vars *vars, t_info *info, double move_speed)
{
	double	air;

	air = -0.001;
	if (move_speed < 0.0)
		air *= -1;
	if (can_move(vars, (int)(info->pos_x + info->dir_x * move_speed + air), \
			(int)(info->pos_y + air)))
		info->pos_x += info->dir_x * move_speed;
	if (can_move(vars, (int)(info->pos_x + air), \
			(int)(info->pos_y + info->dir_y * move_speed + air)))
		info->pos_y += info->dir_y * move_speed;
}

void	move_left_right(t_vars *vars, t_info *info, double move_speed)
{
	double	air;

	air = -0.001;
	if (move_speed < 0.0)
		air *= -1;
	if (can_move(vars, (int)(info->pos_x - info->dir_y * move_speed + air), \
			(int)(info->pos_y + air)))
		info->pos_x -= info->dir_y * move_speed;
	if (can_move(vars, (int)(info->pos_x + air), \
			(int)(info->pos_y + info->dir_x * move_speed + air)))
		info->pos_y += info->dir_x * move_speed;
}

void	rotate_left(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dir_x;
	info->dir_x = info->dir_x * cos(-rot_speed) - info->dir_y \
				* sin(-rot_speed);
	info->dir_y = tmp * sin(-rot_speed) + info->dir_y \
				* cos(-rot_speed);
	tmp = info->plane_x;
	info->plane_x = info->plane_x * cos(-rot_speed) - info->plane_y \
				* sin(-rot_speed);
	info->plane_y = tmp * sin(-rot_speed) + info->plane_y \
				* cos(-rot_speed);
}

void	rotate_right(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dir_x;
	info->dir_x = info->dir_x * cos(rot_speed) - info->dir_y \
				* sin(rot_speed);
	info->dir_y = tmp * sin(rot_speed) + info->dir_y \
				* cos(rot_speed);
	tmp = info->plane_x;
	info->plane_x = info->plane_x * cos(rot_speed) - info->plane_y \
				* sin(rot_speed);
	info->plane_y = tmp * sin(rot_speed) + info->plane_y \
				* cos(rot_speed);
}
