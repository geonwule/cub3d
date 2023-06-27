/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:53:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/28 01:48:37 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_texture(t_vars *vars)
{
	printf("north:%s\n", vars->map.info.north);
	printf("south:%s\n", vars->map.info.south);
	printf("west:%s\n", vars->map.info.west);
	printf("east:%s\n", vars->map.info.east);
}


void	print_color(t_vars *vars)
{
	int i;

	printf("floor:%s\n", vars->map.info.floor);
	printf("ceiling:%s\n", vars->map.info.ceiling);
	i = 0;
	while (i < 3)
	{
		printf("f[%d]: %d\n", i, vars->map.info.f[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("c[%d]: %d\n", i, vars->map.info.c[i]);
		i++;
	}
}

void	print_arr_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_lst(t_list *head)
{
	t_list *cur;

	cur = head;
	while (cur)
	{
		printf("%s", cur->content);
		cur = cur->next;
	}
}
