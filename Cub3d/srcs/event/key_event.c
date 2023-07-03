/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:14:28 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/03 16:14:32 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

int	key_release(int keycode, t_vars *vars)
{
	#ifdef KEY_DEBUG
	if (keycode == W)
        printf("release W\n");
	else if (keycode == A)
        printf("release A\n");
	else if (keycode == S)
        printf("release S\n");
	else if (keycode == D)
        printf("release D\n");
	#endif
	if (keycode >= 0 && keycode <= 255)
		vars->data.keyboard[keycode] = 0;
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	#ifdef KEY_DEBUG
	if (keycode == W)
        printf("press W\n");
	else if (keycode == A)
        printf("press A\n");
	else if (keycode == S)
        printf("press S\n");
	else if (keycode == D)
        printf("press D\n");
	else if (keycode == ESC)
		printf("press ESC\n");
	#endif

	t_info	*info;
	char	**map;

	info = vars->info;
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
	return (0);
}