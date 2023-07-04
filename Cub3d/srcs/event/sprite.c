/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:04:14 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 18:15:41 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_sprite_num(t_vars *vars, char **map, int height, int width)
{
	int	i;
	int	j;

	vars->sprite.sprite_num = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'M' || map[i][j] == 'P' || map[i][j] == 'H')
				vars->sprite.sprite_num++;
			j++;
		}
		i++;
	}
	if (vars->sprite.sprite_num == 0)
		return (0);
	return (1);
}

static t_sp	*malloc_sprite(t_vars *vars, int s_idx, int i, int j)
{
	t_sp	*sp;

	sp = ft_malloc(sizeof(t_sp) * vars->sprite.sprite_num);
	i = -1;
	s_idx = 0;
	while (++i < vars->map.height)
	{
		j = -1;
		while (++j < vars->map.width)
		{
			if (vars->map.arr[i][j] == 'M')
				sp[s_idx].texture = TEX_MONSTER;
			else if (vars->map.arr[i][j] == 'P')
				sp[s_idx].texture = TEX_POTION;
			else if (vars->map.arr[i][j] == 'H')
				sp[s_idx].texture = TEX_NPC;
			else
				continue ;
			sp[s_idx].x = (double)i + 0.5;
			sp[s_idx].y = (double)j + 0.5;
			s_idx++;
		}
	}
	return (sp);
}

static void	init_sprite(t_vars *vars, char **map)
{
	if (!check_sprite_num(vars, map, vars->map.height, vars->map.width))
		return ;
	if (vars->sprite.sp)
		free(vars->sprite.sp);
	vars->sprite.sp = malloc_sprite(vars, 0, -1, -1);
	if (vars->sprite.v_move >= 300 || vars->sprite.v_move <= 0)
		vars->sprite.v_i *= -1;
	vars->sprite.v_move += vars->sprite.v_i;
}

static void	handle_sprite(t_vars *vars, t_info *info, t_sp *sp)
{
	int	*order;
	int	i;

	order = sort_sprite(vars, info, sp);
	i = 0;
	while (i < vars->sprite.sprite_num)
	{
		calculate_sprite(vars, info, order[i], &vars->sprite);
		i++;
	}
	free(order);
}

void	sprite(t_vars *vars)
{
	t_info	*info;

	info = &vars->info;
	init_sprite(vars, vars->map.arr);
	if (vars->sprite.sp)
		handle_sprite(vars, info, vars->sprite.sp);
}
