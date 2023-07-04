/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:13:11 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/04 17:56:02 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr_2d(char ***arr)
{
	int	i;

	if (!(*arr))
		return ;
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

void	free_lst(t_list **head)
{
	t_list	*cur;
	t_list	*next;

	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		cur = next;
	}
}
