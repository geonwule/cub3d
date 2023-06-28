/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:10:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/27 23:22:08 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *str, t_vars *vars)
{
	printf("Error\n");
	printf("%s\n", str);
	free_map(&vars->map);
	vars_free(vars);
	exit(1);
}
