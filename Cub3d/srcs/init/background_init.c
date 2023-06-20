/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:24:20 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/16 19:25:25 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_argb(int a, int rgb[3])
{
	return (a << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	fill_background(t_vars *vars, int ceiling[3], int floor[3])
{
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			if (y < WIN_HEIGHT / 2)
				vars->info->buf[y][x] = create_argb(0, ceiling);
			else
				vars->info->buf[y][x] = create_argb(0, floor);
		}
	}
}
