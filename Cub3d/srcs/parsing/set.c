/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:00:02 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/25 06:20:04 by jonchoi          ###   ########.fr       */
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

void set_color(char **arr, t_vars *vars)
{
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		if (vars->floor)
			print_error("Too many info", vars);
		vars->floor = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if (vars->ceiling)
			print_error("Too many info", vars);
		vars->ceiling = allocate_and_copy_string(arr[1]); 
	}
}

void	set_texture(char **arr, t_vars *vars)
{
	if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
	{
		if (vars->north)
			print_error("Too many info", vars);
		vars->north = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
	{
		if (vars->south)
			print_error("Too many info", vars);
		vars->south = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
	{
		if (vars->west)
			print_error("Too many info", vars);
		vars->west = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
	{
		if (vars->east)
			print_error("Too many info", vars);
		vars->east = allocate_and_copy_string(arr[1]);
	}
}

int		size_arr_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}


/*
head_init();
while()
{
	add_list
}

map_list_to_arr
	- check_valid_map
	- check player

 */
void	set_map(char **arr, t_vars *vars, int fd, char *line)
{
	int i;
	t_list	*cur;

	cur = ft_lstnew(line);
	printf("%s\n", cur->content);
	printf("%s", line);
	i = 0;
//	while (i < size_arr_2d(arr))
//	{
//		
//	}
	free(line);
	free_arr_2d(&arr);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		printf("%s", line);
		arr = ft_split(line, ' ');


		free(line);
		free_arr_2d(&arr);
	}


}
