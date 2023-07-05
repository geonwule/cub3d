/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_and_mouse2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 04:11:57 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:41:34 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_vars *vars, t_info *info, double move_speed)
{
	if (can_move(vars, (int)(info->pos_x + info->dir_x * move_speed), \
			(int)(info->pos_y)))
		info->pos_x += info->dir_x * move_speed;
	if (can_move(vars, (int)(info->pos_x), \
			(int)(info->pos_y + info->dir_y * move_speed)))
		info->pos_y += info->dir_y * move_speed;
}

void	move_left_right(t_vars *vars, t_info *info, double move_speed)
{
	if (can_move(vars, (int)(info->pos_x - info->dir_y * move_speed), \
			(int)(info->pos_y)))
		info->pos_x -= info->dir_y * move_speed;
	if (can_move(vars, (int)(info->pos_x), \
			(int)(info->pos_y + info->dir_x * move_speed)))
		info->pos_y += info->dir_x * move_speed;
}

void	rotate_left_right(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dir_x;
	info->dir_x = info->dir_x * cos(-info->rot_speed) - info->dir_y \
				* sin(-info->rot_speed);
	info->dir_y = tmp * sin(-info->rot_speed) + info->dir_y \
				* cos(-info->rot_speed);
	tmp = info->plane_x;
	info->plane_x = info->plane_x * cos(-info->rot_speed) - info->plane_y \
				* sin(-info->rot_speed);
	info->plane_y = tmp * sin(-info->rot_speed) + info->plane_y \
				* cos(-info->rot_speed);
}

void	rotate_left(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dir_x;
	info->dir_x = info->dir_x * cos(-info->rot_speed) - info->dir_y \
				* sin(-info->rot_speed);
	info->dir_y = tmp * sin(-info->rot_speed) + info->dir_y \
				* cos(-info->rot_speed);
	tmp = info->plane_x;
	info->plane_x = info->plane_x * cos(-info->rot_speed) - info->plane_y \
				* sin(-info->rot_speed);
	info->plane_y = tmp * sin(-info->rot_speed) + info->plane_y \
				* cos(-info->rot_speed);
}

void	rotate_right(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dir_x;
	info->dir_x = info->dir_x * cos(info->rot_speed) - info->dir_y \
				* sin(info->rot_speed);
	info->dir_y = tmp * sin(info->rot_speed) + info->dir_y \
				* cos(info->rot_speed);
	tmp = info->plane_x;
	info->plane_x = info->plane_x * cos(info->rot_speed) - info->plane_y \
				* sin(info->rot_speed);
	info->plane_y = tmp * sin(info->rot_speed) + info->plane_y \
				* cos(info->rot_speed);
}
