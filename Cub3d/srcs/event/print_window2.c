/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 05:05:28 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 18:51:41 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	level_up(t_vars *vars)
{
	char	*level_str;

	if (vars->data.hunt != 0 && vars->data.hunt % 2 == 0)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.lv, \
				WIN_WIDTH / 9 * 2, WIN_HEIGHT / 5 * 2);
		vars->data.level += 1;
		vars->data.hunt = 0;
	}
	level_str = ft_itoa(vars->data.level);
	mlx_string_put(vars->mlx, vars->win, 50, 710, 0xFFFFFF, level_str);
	free(level_str);
}

static void	warning_message(t_vars *vars)
{
	if (vars->data.m_num)
		return ;
	vars->data.warning_time++;
	if (vars->data.warning_time % 7 == 0)
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.w_messege \
		, WIN_WIDTH / 100 * 20, WIN_HEIGHT / 100 * 35);
}

static void	quest_progress(t_vars *vars)
{
	char	*str;
	char	*kill;

	if (vars->data.quest_monster_num == 0)
	{
		mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 100 * 45, \
			WIN_HEIGHT / 100 * 2, 0xFFFFFF, "quest clear!! go back to NPC");
		vars->data.quest_num = 2;
		return ;
	}
	kill = ft_itoa(30 - vars->data.quest_monster_num);
	str = ft_strjoin("quest progress : 30 / ", kill);
	free(kill);
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 100 * 45, \
			WIN_HEIGHT / 100 * 2, 0xFFFFFF, str);
	free(str);
}

static void	npc_quest(t_vars *vars)
{
	if (vars->data.quest_num != 0)
		quest_progress(vars);
	if (vars->data.npc_talk == 0)
		return ;
	if (vars->data.quest_num == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.quest_start, \
			WIN_WIDTH / 100 * 35, WIN_HEIGHT / 100 * 30);
	else if (vars->data.quest_num == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.quest_ing, \
			WIN_WIDTH / 100 * 35, WIN_HEIGHT / 100 * 30);
	else if (vars->data.quest_num == 2)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.quest_end, \
			WIN_WIDTH / 100 * 35, WIN_HEIGHT / 100 * 30);
}

void	print_window2(t_vars *vars)
{
	level_up(vars);
	warning_message(vars);
	npc_quest(vars);
	if (vars->data.hp_before > vars->data.hp)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.damage, \
			WIN_WIDTH / 100 * 12, 0);
	vars->data.hp_before = vars->data.hp;
}
