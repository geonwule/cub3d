/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:11 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/27 23:16:50 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_map(t_map *map)
{
	if (map->info.north)
		free(map->info.north);
	if (map->info.south)
		free(map->info.south);
	if (map->info.west)
		free(map->info.west);
	if (map->info.east)
		free(map->info.east);
	if (map->info.floor)
		free(map->info.floor);
	if (map->info.ceiling)
		free(map->info.ceiling);
	if (map->arr)
		free_arr_2d(&map->arr);
}
