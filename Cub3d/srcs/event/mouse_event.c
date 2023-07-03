/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:15:25 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 04:44:00 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_resurrection(t_vars *vars)
{
	reset_game(vars);
	vars->data.dead_check = 0;
}

static void	talk_npc_agree(t_vars *vars)
{
	vars->data.npc_talk = 0;
	vars->data.quest_num = 1;
}

static void	talk_npc_negative(t_vars *vars)
{
	vars->data.npc_talk = 0;
}

int	handle_mouse_button(int button, int x, int y, void *args)
{
	t_vars	*vars;

	vars = (t_vars *)args;
	if (vars->data.dead_check && x >= 800 && x <= 860 && y >= 380 && y <= 400)
		player_resurrection(vars);
	else if (vars->data.npc_talk && vars->data.quest_num == 0 \
		&& x >= 800 && x <= 850 && y >= 420 && y <= 435)
		talk_npc_agree(vars);
	else if (vars->data.npc_talk \
		&& ((x >= 870 && x <= 920 && y >= 420 && y <= 435) \
		|| (x >= 435 && x <= 510 && y >= 420 && y <= 435)))
		talk_npc_negative(vars);
	else if (button == 1 && vars->data.dead_check == 0 && !vars->data.npc_talk)
		attack(vars);
	return (0);
}

int	handle_mouse_move(int x, int y, void *args)
{
	t_vars	*vars;

	vars = (t_vars *)args;
	if (vars->data.npc_talk)
		return (0);
	vars->data.mouse_old_x = vars->data.mouse_x;
	vars->data.mouse_old_y = vars->data.mouse_y;
	vars->data.mouse_x = x;
	vars->data.mouse_y = y;
	return (0);
}
