/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:17:00 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/24 20:29:07 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern char	map[15][34]; //tmp

int	can_move(t_vars *vars, int x, int y)
{
	char	spot;

	spot = map[x][y];
	if (spot == 'P')
	{
		map[x][y] = '0';
		if (vars->hp < 3)
			vars->hp++;
	}
	else if (spot == '0' || spot == 'N' || spot == 'S' \
		|| spot == 'W' || spot == 'E' || spot == 'b')
		return (1);
	return (0);
}

static void	key_check(t_vars *vars)
{
	t_info	*info = vars->info;
	
	if (vars->keyboard[ESC])
       	exit_game(vars);
	if (vars->keyboard[W])
	{
		if (can_move(vars, (int)(info->posX + info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
				info->posX += info->dirX * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY + info->dirY * info->moveSpeed)))
			info->posY += info->dirY * info->moveSpeed;
			//printf("posX = %d, dirX = %d, posY = %d, dirY = %d\n", (int)info->posX, (int)info->dirX, (int)info->posY, (int)info->dirY);
	}
	if (vars->keyboard[S])
	{
		if (can_move(vars, (int)(info->posX - info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX -= info->dirX * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY - info->dirY * info->moveSpeed)))
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (vars->keyboard[D])
	{
		if (can_move(vars, (int)(info->posX + info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX += info->dirY * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY - info->dirX * info->moveSpeed)))
			info->posY -= info->dirX * info->moveSpeed;
	}
	if (vars->keyboard[A])
	{
		if (can_move(vars, (int)(info->posX - info->dirY * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX -= info->dirY * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY + info->dirX * info->moveSpeed)))
			info->posY += info->dirX * info->moveSpeed;
	}
	if (vars->keyboard[LEFT])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (vars->keyboard[RIGHT])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
}

static void mini_map(t_vars *vars)
{
	int mini_width, mini_height;

	mini_width = 34;
	mini_height = 15;
	
	void	*mini_back = mlx_new_image(vars->mlx, mini_width * 10, mini_height * 10);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
		{
			mlx_pixel_put(vars->mlx, mini_back, y, x, 0);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, mini_back, 0, 0);
	for (int x = 0; x < mini_height; x++)
	{
		for (int y = 0; y < mini_width; y++)
		{
			if (x == (int)vars->info->posX && y == (int)vars->info->posY)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player_x, y * 10, x * 10);
			else if (map[x][y] == '1')// wall
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'M')// monster
				mlx_put_image_to_window(vars->mlx, vars->win, vars->monster_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'B')// break 벽
				mlx_put_image_to_window(vars->mlx, vars->win, vars->door_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == 'P')// break 벽
				mlx_put_image_to_window(vars->mlx, vars->win, vars->potion_x, y * 10, x * 10); // 10x10 xpm이기때문에
			else if (map[x][y] == '0' || map[x][y] == 'b')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->empty_x, y * 10, x * 10);
		}
	}
	int x = (int)vars->info->posX;
	int y = (int)vars->info->posY;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->dir_x, y * 10 + vars->info->dirY * 7, x * 10 + vars->info->dirX * 7); //dir
}

void	draw_mlx(t_vars *vars)
{
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			vars->info->img.data[y * WIN_WIDTH + x] = vars->info->buf[y][x];
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->info->img.img, 0, 0);
}


void	aim_point(t_vars *vars)
{
	int x, y;
	if (vars->gun_change)
	{
		vars->gun = ft_xpm_file_to_image(vars->mlx, "texture/hand2.xpm", &x, &y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->gun, WIN_WIDTH / 10 * 3, WIN_HEIGHT / 9 * 6);
		vars->gun_change = 0;
	}
	else
	{
		vars->gun = ft_xpm_file_to_image(vars->mlx, "texture/hand1.xpm", &x, &y);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->gun, WIN_WIDTH / 9 * 1, WIN_HEIGHT / 9 * 5);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->aim, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void	damaged_or_recovery(t_vars *vars)
{
	if (vars->hp_before > vars->hp)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->damage, WIN_WIDTH / 100 * 12, 0);
	vars->hp_before = vars->hp;
}

void	monster_come_on(t_vars *vars, int x, int y)
{
	t_info	*info = vars->info;

	if (!vars->monster_come || ++vars->m_speed % 30 != 0 \
		|| map[vars->m_pos[X]][vars->m_pos[Y]] != 'M')
		return ;

	// printf("map[%d][%d] = %c\n", vars->m_pos[X], vars->m_pos[Y], map[vars->m_pos[X]][vars->m_pos[Y]]);
	
	if ((int)info->posX < x && map[x - 1][y] == '0')
	{
		if (((int)info->posX == x - 1 && (int)info->posY == y) && vars->hp > 0)
			vars->hp -= 1;
		else
		{
			map[x][y] = '0';
			map[x - 1][y] = 'M';
			vars->m_pos[X] -= 1;
		}		
	}
	else if ((int)info->posX > x && map[x + 1][y] == '0')
	{
		if (((int)info->posX == x + 1 && (int)info->posY == y))
			vars->hp -= 1;
		else
		{
			map[x][y] = '0';
			map[x + 1][y] = 'M';
			vars->m_pos[X] += 1;
		}
	}
	x = vars->m_pos[X];
	if ((int)info->posY < y && map[x][y - 1] == '0')
	{
		if ((int)info->posX == x && (int)info->posY == y - 1)
			vars->hp -= 1;
		else
		{
			map[x][y] = '0';
			map[x][y - 1] = 'M';
			vars->m_pos[Y] -= 1;
		}
	}
	else if ((int)info->posY > y && map[x][y + 1] == '0')
	{
		if ((int)info->posX == x && (int)info->posY == y + 1)
			vars->hp -= 1;
		else
		{
			map[x][y] = '0';
			map[x][y + 1] = 'M';
			vars->m_pos[Y] += 1;
		}
	}
}

void	hp_exp(t_vars *vars)
{
	if (vars->hp == 3)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->hp3, WIN_WIDTH * 0, WIN_HEIGHT / 100 * 98);
	else if (vars->hp == 2)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->hp2, WIN_WIDTH * 0, WIN_HEIGHT / 100 * 98);
	else if (vars->hp == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->hp1, WIN_WIDTH * 0, WIN_HEIGHT / 100 * 98);
	else if (vars->hp == 0)
	{
		vars->dead_check = 1;
		return ;
	}
	if (vars->hunt % 2 == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->exp1, WIN_WIDTH / 100 * 34, WIN_HEIGHT / 100 * 98);
	else if (vars->hunt % 2 == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->exp2, WIN_WIDTH / 100 * 34, WIN_HEIGHT / 100 * 98);
}

void	level_up(t_vars *vars)
{
	char	*level_str;
	if (vars->hunt != 0 && vars->hunt % 2 == 0)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->lv, WIN_WIDTH / 9 * 2, WIN_HEIGHT / 5 * 2);
		vars->level += 1;
		vars->hunt = 0;
	}
	level_str = ft_itoa(vars->level); //overflow protect need!
	mlx_string_put(vars->mlx, vars->win, 50, 710, 0xFFFFFF, level_str);
	
	free(level_str);
}


int	dead_check_game_end(t_vars *vars)
{
	// int	i;

	// i = 0;
	if (!vars->dead_check)
		return (0);
	if (vars->dead_check)
	{
		if (vars->keyboard[ESC])
			exit_game(vars);
		else if (vars->keyboard[P])
		{
			reset_game(vars);
			vars->dead_check = 0;
			return (0);
		}
	}
	return (1);
}

void	warning_message(t_vars *vars)
{
	if (vars->m_num)
		return ;
	vars->warning_time++;
	if (vars->warning_time % 7 == 0) //깜빡이게
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->w_messege \
		, WIN_WIDTH / 100 * 20, WIN_HEIGHT / 100 * 35);
}

void	monster_rezen(t_vars *vars)
{
	int			i;
	int			j;

	/*need parsing
	vars->map->height = 15;
	vars->map->width = 34;
	*/

	// i = 0;
	// while (i < 15)
	// {
	// 	j = 0;
	// 	while (j < 34)
	// 	{
	// 		if (map[i][j] == 'M')
	// 			return ;
	// 		j++;
	// 	}
	// 	i++;
	// }
	if (vars->m_num)
		return ;
	if (vars->warning_time < 50) //warning_time
		return ;
	vars->warning_time = 0;
	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 34)
		{
			if (i > 7 && j > 24)
				break ;
			if (map[i][j] == '0' && random_generator(2) \
				&& i != (int)vars->info->posX && j != (int)vars->info->posY)
			{
				map[i][j] = 'M';
				vars->m_num++;
				usleep(1);
			}
			j++;
		}
		i++;
	}
}

int	rendering(t_vars *vars)
{
	if (dead_check_game_end(vars))
		return (0);
	monster_rezen(vars);
	monster_come_on(vars, vars->m_pos[X], vars->m_pos[Y]);

	key_check(vars);
	mlx_clear_window(vars->mlx, vars->win); // clear window
	fill_background(vars, vars->c, vars->f); // study_need // fill back ground
	map_set(vars);
	draw_mlx(vars);

	aim_point(vars);
	hp_exp(vars);
	level_up(vars);
	warning_message(vars);

	mini_map(vars);	

	damaged_or_recovery(vars);
	if (vars->dead_check)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->dead, WIN_WIDTH / 100 * 33, WIN_HEIGHT / 100 * 30);
	return (0);
}