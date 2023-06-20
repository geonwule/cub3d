/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:15:25 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/20 12:10:40 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern char	map[15][34]; //tmp

int	handle_mouse_button(int button, int x, int y, void *args)
{
	t_vars	*vars;
	vars = (t_vars *)args;
	printf("in mouse_handel\nbutton = %d, x = %d y = %d, vars = %p\n", button, x, y, vars);
	if (button == 1)
	{
		int x, y;
		void	*shot = mlx_xpm_file_to_image(vars->mlx, "texture/shot.xpm", &x, &y);
		mlx_put_image_to_window(vars->mlx, vars->win, shot, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		monster_kill(vars);
		printf("mouse_button\n");
	}
	return (0);
}

// int is_weak_brick(t_vars *vars, int x, int y)
// {
// 	char	spot;

// 	spot = map[x][y];
// 	if (spot == 'B' || spot == 'b')
// 	{
// 		printf("can break or build\n");//tmp
// 		return (1);
// 	}
// 	return (0);
// }

int	handle_mouse_move(int x, int y, void *args)
{
	t_vars	*vars;
	vars = (t_vars *)args;
	printf("in mouse_handel\nx = %d y = %d, vars = %p\n", x, y, vars);

	t_info	*info = vars->info;
	if (x > (WIN_WIDTH / 2 + WIN_WIDTH / 3))//left
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	
	if (x < (WIN_WIDTH / 2 - + WIN_WIDTH / 3))//right
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

	// t_info *info = vars->info;

	// if (keycode == SPACE)
	// {
	// 	int	tmp_x, tmp_y;
	// 	tmp_x = -1;
	// 	tmp_y = -1;
	// 	if (is_weak_brick(vars, (int)(info->posX + info->dirX * info->moveSpeed + 0.5) \
	// 		, (int)(info->posY)))
	// 	{
	// 		tmp_x = (int)(info->posX + info->dirX * info->moveSpeed + 0.5);
	// 	}
	// 	if (is_weak_brick(vars, (int)(info->posX) \
	// 		, (int)(info->posY + 1 + info->dirY * info->moveSpeed + 0.5)))
	// 	{
	// 		tmp_y = (int)(info->posY + 1 + info->dirY * info->moveSpeed + 0.5);
	// 	}
	// 	if (tmp_x == -1 || tmp_y == -1)
	// 		return (0);
	// 	if (map[tmp_x][tmp_y] == 'B')
	// 		map[tmp_x][tmp_y] = 'b';
	// 	else if (map[tmp_x][tmp_y] == 'b')
	// 		map[tmp_x][tmp_y] = 'B';

	// 	//tmp
	// 	printf("map=\n");
	// 	//extern char	map[15][34]; //tmp
	// 	for (int i = 0; i < 15; i++)
	// 		printf("%s\n", map[i]);
	// }