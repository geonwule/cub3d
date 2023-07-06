/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:10:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/06 15:21:04 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *str, t_vars *vars)
{
	printf("Error\n");
	printf("%s\n", str);
	free_map(&vars->map);
	exit(EXIT_FAILURE);
}
