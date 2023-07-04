/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_and_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:17:22 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 18:12:46 by geonwule         ###   ########.fr       */
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
	else if (spot == '0' || spot == 'N' || spot == 'S' \
		|| spot == 'W' || spot == 'E' || spot == 'b')
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
		move_forward_backward(vars, info, info->moveSpeed);
	if (vars->data.keyboard[S])
		move_forward_backward(vars, info, -info->moveSpeed);
	if (vars->data.keyboard[D])
		move_left_right(vars, info, -info->moveSpeed);
	if (vars->data.keyboard[A])
		move_left_right(vars, info, info->moveSpeed);
	if (vars->data.keyboard[LEFT])
		rotate_left(info, info->rotSpeed);
	if (vars->data.keyboard[RIGHT])
		rotate_right(info, info->rotSpeed);
}

static void	mouse_check(t_vars *vars)
{
	t_info	*info;
	double	tmp;

	info = &vars->info;
	if (vars->data.mouse_x > vars->data.mouse_old_x)
		rotate_left(info, info->rotSpeed);
	if (vars->data.mouse_x < vars->data.mouse_old_x)
		rotate_right(info, info->rotSpeed);
	if (++vars->data.render_i % 5 == 0)
	{
		vars->data.mouse_old_x = vars->data.mouse_x;
		vars->data.mouse_old_y = vars->data.mouse_y;
	}
}

void	check_key_and_mouse(t_vars *vars)
{
	key_check(vars);
	mouse_check(vars);
}
