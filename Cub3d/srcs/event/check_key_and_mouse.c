/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_and_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:17:22 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/17 12:57:06 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move(t_vars *vars, int x, int y)
{
	char	spot;

	spot = vars->map.arr[x][y];
	if (spot == 'P')
	{
		vars->map.arr[x][y] = '0';
		if (vars->data.hp < 3)
			vars->data.hp++;
		return (1);
	}
	else if (spot == '0' || spot == 'b')
		return (1);
	return (0);
}

static void	key_check(t_vars *vars)
{
	t_info	*info;

	info = &vars->info;
	if (vars->data.keyboard[ESC])
		exit_game(vars);
	if (vars->data.keyboard[W])
		move_forward_backward(vars, info, info->move_speed);
	if (vars->data.keyboard[S])
		move_forward_backward(vars, info, -info->move_speed);
	if (vars->data.keyboard[D])
		move_left_right(vars, info, -info->move_speed);
	if (vars->data.keyboard[A])
		move_left_right(vars, info, info->move_speed);
	if (vars->data.keyboard[LEFT])
		rotate_left(info, info->rot_speed);
	if (vars->data.keyboard[RIGHT])
		rotate_right(info, info->rot_speed);
}

static void	mouse_check(t_vars *vars)
{
	t_info	*info;

	info = &vars->info;
	if (vars->data.mouse_x > vars->data.mouse_old_x)
	{
		rotate_left(info, info->rot_speed \
			* abs(vars->data.mouse_x - vars->data.mouse_old_x) / 100);
	}
	if (vars->data.mouse_x < vars->data.mouse_old_x)
	{
		rotate_right(info, info->rot_speed \
		* abs(vars->data.mouse_x - vars->data.mouse_old_x) / 100);
	}
	// up & down... 
	// if (vars->data.mouse_y < vars->data.mouse_old_y)
	// {
	// 	rotate_up(info, info->rot_speed \
	// 	* abs(vars->data.mouse_y - vars->data.mouse_old_y) / 100);
	// }
	// if (vars->data.mouse_y > vars->data.mouse_old_y)
	// {
	// 	rotate_down(info, info->rot_speed \
	// 	* abs(vars->data.mouse_y - vars->data.mouse_old_y) / 100);
	// }
	if (vars->data.npc_talk == 0)
		mlx_mouse_move(vars->win, vars->data.mouse_old_x, vars->data.mouse_old_y);
}

void	check_key_and_mouse(t_vars *vars)
{
	key_check(vars);
	mouse_check(vars);
}
