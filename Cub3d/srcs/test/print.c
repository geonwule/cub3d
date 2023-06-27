/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:27:39 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/27 18:34:26 by jonchoi          ###   ########.fr       */
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
	int i;

	printf("vars->floor:%s\n", vars->floor);
	printf("vars->ceiling:%s\n", vars->ceiling);
	i = 0;
	while (i < 3)
	{
		printf("f[%d]: %d\n", i, vars->f[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("c[%d]: %d\n", i, vars->c[i]);
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
