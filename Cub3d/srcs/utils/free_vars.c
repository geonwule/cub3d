/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:13:35 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 12:36:51 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_vars(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->info.texture)
	{
		while (i < TEX_NUM)
		{
			free(vars->info.texture[i]);
			i++;
		}
		free(vars->info.texture);
	}
	if (vars->sprite.sp)
		free(vars->sprite.sp);
}
