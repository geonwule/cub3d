/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_and_mouse2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 04:11:57 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 04:16:43 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_vars *vars, t_info *info, double move_speed)
{
	if (can_move(vars, (int)(info->posX + info->dirX * move_speed), \
			(int)(info->posY)))
		info->posX += info->dirX * move_speed;
	if (can_move(vars, (int)(info->posX), \
			(int)(info->posY + info->dirY * move_speed)))
		info->posY += info->dirY * move_speed;
}

void	move_left_right(t_vars *vars, t_info *info, double move_speed)
{
	if (can_move(vars, (int)(info->posX - info->dirY * move_speed), \
			(int)(info->posY)))
		info->posX -= info->dirY * move_speed;
	if (can_move(vars, (int)(info->posX), \
			(int)(info->posY + info->dirX * move_speed)))
		info->posY += info->dirX * move_speed;
}

void	rotate_left_right(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dirX;
	info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY \
				* sin(-info->rotSpeed);
	info->dirY = tmp * sin(-info->rotSpeed) + info->dirY \
				* cos(-info->rotSpeed);
	tmp = info->planeX;
	info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY \
				* sin(-info->rotSpeed);
	info->planeY = tmp * sin(-info->rotSpeed) + info->planeY \
				* cos(-info->rotSpeed);
}

void	rotate_left(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dirX;
	info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY \
				* sin(-info->rotSpeed);
	info->dirY = tmp * sin(-info->rotSpeed) + info->dirY \
				* cos(-info->rotSpeed);
	tmp = info->planeX;
	info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY \
				* sin(-info->rotSpeed);
	info->planeY = tmp * sin(-info->rotSpeed) + info->planeY \
				* cos(-info->rotSpeed);
}

void	rotate_right(t_info *info, double rot_speed)
{
	double	tmp;

	tmp = info->dirX;
	info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY \
				* sin(info->rotSpeed);
	info->dirY = tmp * sin(info->rotSpeed) + info->dirY \
				* cos(info->rotSpeed);
	tmp = info->planeX;
	info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY \
				* sin(info->rotSpeed);
	info->planeY = tmp * sin(info->rotSpeed) + info->planeY \
				* cos(info->rotSpeed);
}
