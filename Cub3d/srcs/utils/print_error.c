/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:10:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 18:03:52 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *str, t_vars *vars)
{
	printf("Error\n");
	printf("%s\n", str);
	free_map(&vars->map);
	printf("free map\n");
	free_vars(vars);
	printf("free vars\n");
	exit(1);
}
