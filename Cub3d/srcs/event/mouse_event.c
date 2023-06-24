/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:15:25 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/24 17:43:20 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern char	map[15][34]; //tmp

int	handle_mouse_button(int button, int x, int y, void *args)
{
	t_vars	*vars;
	vars = (t_vars *)args;
	// printf("in mouse_handel\nbutton = %d, x = %d y = %d, vars = %p\n", button, x, y, vars);
	if (button == 1)
		attack(vars);
	return (0);
}

int	handle_mouse_move(int x, int y, void *args)
{
	t_vars	*vars;
	vars = (t_vars *)args;
	printf("in mouse_handel\nx = %d y = %d, vars = %p\n", x, y, vars);

	t_info	*info = vars->info;
	if (x > (WIN_WIDTH / 2))// + WIN_WIDTH / 3))//left
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	
	if (x < (WIN_WIDTH / 2))//- + WIN_WIDTH / 3))//right
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	return (0);
}