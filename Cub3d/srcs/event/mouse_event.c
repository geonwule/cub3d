/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:15:25 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/27 13:42:03 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_resurrection(t_vars *vars)
{
	reset_game(vars);
	vars->dead_check = 0;
}

static void	talk_npc_agree(t_vars *vars)
{
	vars->npc_talk = 0;
	vars->quest_num = 1;
}

static void	talk_npc_negative(t_vars *vars)
{
	vars->npc_talk = 0;
}

int	handle_mouse_button(int button, int x, int y, void *args)
{
	t_vars	*vars;

	vars = (t_vars *)args;
	if (vars->dead_check && x >= 800 && x <= 860 && y >= 380 && y <= 400)
		player_resurrection(vars);
	else if (vars->npc_talk && vars->quest_num == 0 \
		&& x >= 800 && x <= 850 && y >= 420 && y <= 435)
		talk_npc_agree(vars);
	else if (vars->npc_talk && ((x >= 870 && x <= 920 && y >= 420 && y <= 435) \
		|| (x >= 435 && x <= 510 && y >= 420 && y <= 435)))
		talk_npc_negative(vars);
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
	vars->mouse_old_y = vars->mouse_y;
	vars->mouse_x = x;
	vars->mouse_y = y;
	//printf("in mouse_handel\nx = %d old_x = %d, vars = %p\n", vars->mouse_x, vars->mouse_old_x, vars);
	return (0);
}