/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:15:25 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/27 13:31:07 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern char	map[15][34]; //tmp

int	handle_mouse_button(int button, int x, int y, void *args)
{
	t_vars	*vars;
	vars = (t_vars *)args;
	// printf("in mouse_handel\nbutton = %d, x = %d y = %d, vars = %p\n", button, x, y, vars);
	if (vars->dead_check && x >= 800 && x <= 860 && y >= 380 && y <= 400)
	{
		reset_game(vars);
		vars->dead_check = 0;
		return (0);
	}
	else if (vars->npc_talk && x >= 800 && x <= 850 && y >= 420 && y <= 435)
	{
		vars->npc_talk = 0;
		vars->quest_num = 1;
	}
	else if (vars->npc_talk && ((x >= 870 && x <= 920 && y >= 420 && y <= 435) \
		|| (x >= 435 && x <= 510 && y >= 420 && y <= 435)))
		vars->npc_talk = 0;
	else if (button == 1 && vars->dead_check == 0 && !vars->npc_talk)
		attack(vars);
	return (0);
}

int	handle_mouse_move(int x, int y, void *args)
{
	t_vars	*vars;
	vars = (t_vars *)args;

	if (vars->npc_talk)
		return (0);
	vars->mouse_old_x = vars->mouse_x;
	vars->mouse_x = x;
	vars->mouse_y = y;
	printf("in mouse_handel\nx = %d old_x = %d, vars = %p\n", vars->mouse_x, vars->mouse_old_x, vars);
	// t_info	*info = vars->info;
	// if (x > (WIN_WIDTH / 2))// + WIN_WIDTH / 3))//left
	// {
	// 	//both camera direction and camera plane must be rotated
	// 	double oldDirX = info->dirX;
	// 	info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
	// 	info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
	// 	double oldPlaneX = info->planeX;
	// 	info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
	// 	info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
		
	// 	// info->dirX *= 0.05;
	// 	// info->dirY *= 0.05;
	// 	// info->planeX *= 0.05;
	// 	// info->planeY *= 0.05;
	// }
	
	// if (x < (WIN_WIDTH / 2))//- + WIN_WIDTH / 3))//right
	// {
	// 	//both camera direction and camera plane must be rotated
	// 	double oldDirX = info->dirX;
	// 	info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
	// 	info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
	// 	double oldPlaneX = info->planeX;
	// 	info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
	// 	info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	// }
	return (0);
}