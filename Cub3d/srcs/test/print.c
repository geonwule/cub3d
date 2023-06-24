/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:05:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/25 00:53:17 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_texture(t_vars *vars)
{
	printf("vars->north:%s\n", vars->north);
	printf("vars->south:%s\n", vars->south);
	printf("vars->west:%s\n", vars->west);
	printf("vars->east:%s\n", vars->east);
}


void	print_color(t_vars *vars)
{
	printf("vars->floor:%s\n", vars->floor);
	printf("vars->ceiling:%s\n", vars->ceiling);
}
