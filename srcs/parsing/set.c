/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:00:02 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/23 18:40:06 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
set_texture()
set_color();
set_map();
*/

static char *allocate_and_copy_string(char *src)
{
    char *dst;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src));
    if (!dst)
	{
        printf("malloc error\n");
        exit(1);
    }
    dst[ft_strlen(src) - 1] = '\0';		// ft_strlen(src) - 1 : delete '\n'
    ft_memcpy(dst, src, ft_strlen(src) - 1);
    return (dst);
}

int	set_texture(char **arr, t_vars *vars)
{
		printf("Hi, Im check dir\n");
		if (!ft_strncmp(arr[0], "NO", 2))
		{
			printf("Find NO\n");
			vars->north = allocate_and_copy_string(arr[1]);
			return (1);
		}
		else if (!ft_strncmp(arr[0], "SO", 2))
		{
			printf("Find SO\n");
			vars->south = allocate_and_copy_string(arr[1]);
			return (1);
		}
		else if (!ft_strncmp(arr[0], "WE", 2))
		{
			printf("Find WE\n");

			vars->west = allocate_and_copy_string(arr[1]);
			return (1);
		}
		else if (!ft_strncmp(arr[0], "EA", 2))
		{
			printf("Find EA\n");

			vars->east = allocate_and_copy_string(arr[1]);
			return (1);
		}
		return (0);
}
