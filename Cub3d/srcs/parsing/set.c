/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:00:02 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/23 19:27:07 by jonchoi          ###   ########.fr       */
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

int set_color(char **arr, t_vars *vars)
{
	printf("Hi, Im set color;\n");
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		printf("Find color F\n");
		return (1);
	}
	else if (!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		printf("Find color C\n");
		return (1);
	}
	return (0);
}

int	set_texture(char **arr, t_vars *vars)
{
		printf("Hi, Im set texture\n");
		if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
		{
			printf("Find NO\n");
			vars->north = allocate_and_copy_string(arr[1]);
			return (1);
		}
		else if (!ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
		{
			printf("Find SO\n");
			vars->south = allocate_and_copy_string(arr[1]);
			return (1);
		}
		else if (!ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
		{
			printf("Find WE\n");

			vars->west = allocate_and_copy_string(arr[1]);
			return (1);
		}
		else if (!ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
		{
			printf("Find EA\n");

			vars->east = allocate_and_copy_string(arr[1]);
			return (1);
		}
		return (0);
}
