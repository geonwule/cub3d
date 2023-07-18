/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:14:28 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 18:14:21 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int keycode, t_vars *vars)
{
	if (keycode >= 0 && keycode <= 255)
		vars->data.keyboard[keycode] = 0;
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	t_info	*info;
	char	**map;

	info = &vars->info;
	map = vars->map.arr;
	if (keycode == P)
		reset_game(vars);
	if (vars->data.npc_talk)
		return (0);
	if (keycode >= 0 && keycode <= 255)
		vars->data.keyboard[keycode] = 1;
	if (keycode == N || keycode == M)
		adjust_gamespeed(info, keycode);
	if (keycode == SPACE)
		attack(vars);
	if (keycode == Q)
		turn_back(info);
	if (keycode == B)
		open_door_tell_npc(vars, map);
	if (keycode == R)
		return_ellinia(vars);
	if (keycode == TAB)
		change_mini_map(vars);
	return (0);
}
