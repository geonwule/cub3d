/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 03:03:03 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 03:43:45 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_init_vars1(t_vars *vars)
{
	vars->data.monster_come = 0;
	vars->data.m_num = 0;
	vars->data.warning_time = 0;
	vars->data.hand_change = 0;
	vars->data.hp = 3;
	vars->data.hp_before = 3;
	vars->data.hunt = 0;
	vars->data.level = 1;
	vars->data.dead_check = 0;
	vars->data.m_speed = 0;
	vars->data.npc_talk = 0;
	vars->data.quest_num = 0;
	vars->data.quest_monster_num = 30;
	vars->data.mouse_x = WIN_WIDTH / 2;
	vars->data.mouse_old_x = WIN_WIDTH / 2;
	vars->data.mouse_y = WIN_HEIGHT / 2;
	vars->data.render_i = 0;
}

static void	process_init_vars2(t_vars *vars)
{
	int	i;

	vars->sprite.sp = NULL;
	vars->sprite.v_move = 64;
	vars->sprite.v_i = 20;
	vars->sprite.u_div = 1.5;
	vars->sprite.v_div = 1.5;
	i = 0;
	while (i < 1000)
	{
		vars->data.keyboard[i] = 0;
		i++;
	}
}

void	init_vars(t_vars *vars)
{
	process_init_vars1(vars);
	process_init_vars2(vars);
}
