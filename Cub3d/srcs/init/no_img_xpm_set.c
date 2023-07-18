/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_xpm_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 03:13:33 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 03:14:26 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_img_xpm_set1(t_vars *vars, int x, int y)
{
	vars->mini.player_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_PLAYER), &x, &y);
	vars->mini.empty_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_EMPTY), &x, &y);
	vars->mini.wall_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_WALL), &x, &y);
	vars->mini.monster_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_MONSTER), &x, &y);
	vars->mini.door_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_DOOR), &x, &y);
	vars->mini.potion_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_POTION), &x, &y);
	vars->mini.dir_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_DIR), &x, &y);
	vars->mini.npc_x = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, M_NPC), &x, &y);
}

static void	process_img_xpm_set2(t_vars *vars, int x, int y)
{
	vars->xpm.quest_start = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, N_QUEST1), &x, &y);
	vars->xpm.quest_ing = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, N_QUEST2), &x, &y);
	vars->xpm.quest_end = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, N_QUEST3), &x, &y);
	vars->xpm.dead = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, E_DEAD), &x, &y);
	vars->xpm.damage = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, E_DAMAGE), &x, &y);
	vars->xpm.aim = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, E_AIM), &x, &y);
	vars->xpm.w_messege = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, E_WARNING), &x, &y);
	vars->xpm.hand1 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, E_HAND1), &x, &y);
	vars->xpm.hand2 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, E_HAND2), &x, &y);
	vars->xpm.hp1 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, U_HP1), &x, &y);
	vars->xpm.hp2 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, U_HP2), &x, &y);
	vars->xpm.hp3 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, U_HP3), &x, &y);
	vars->xpm.exp1 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, U_EXP1), &x, &y);
	vars->xpm.exp2 = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, U_EXP2), &x, &y);
	vars->xpm.lv = ft_xpm_file_to_image(vars->mlx, ft_strjoin(vars->path, U_LEVEL), &x, &y);
}

void	img_xpm_set(t_vars *vars)
{
	process_img_xpm_set1(vars, 0, 0);
	process_img_xpm_set2(vars, 0, 0);
}
