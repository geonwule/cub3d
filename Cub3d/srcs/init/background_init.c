/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:24:20 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 18:12:21 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_argb(int a, int rgb[3])
{
	return (a << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	fill_background(t_vars *vars, int ceiling[3], int floor[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				vars->info.buf[i][j] = create_argb(0, ceiling);
			else
				vars->info.buf[i][j] = create_argb(0, floor);
			j++;
		}
		i++;
	}
}
