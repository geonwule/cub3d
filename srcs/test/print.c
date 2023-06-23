/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:05:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/23 17:12:08 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_texture(t_vars *vars)
{
	printf("vars->north: %s\n", vars->north);
	printf("vars->south: %s\n", vars->south);
	printf("vars->west: %s\n", vars->west);
	printf("vars->east: %s\n", vars->east);
}
