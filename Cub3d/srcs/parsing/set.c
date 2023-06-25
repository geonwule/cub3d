/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:00:02 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/25 17:20:50 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *allocate_and_copy_string(char *src)
{
    char *dst;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src));
    if (!dst)
	{
//		print_error("dst malloc err in allocate_and_copy_string func", vars);		// need vars argu
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

void	init_map_arr(t_vars *vars, t_list *head)
{
	int i;
	int j;
	t_list	*cur;

	vars->map.arr = (char **)malloc(sizeof(char *) * (vars->map.height + 1));
	if (!vars->map.arr)
		return ;
	vars->map.arr[vars->map.height] = NULL;
	i = 0;
	cur = head;
	while (cur)
	{
		vars->map.arr[i] = (char *)malloc(sizeof(char) * vars->map.width);
		if (!vars->map.arr[i])
			return ;
		ft_memcpy(vars->map.arr[i], cur->content, ft_strlen(cur->content) - 1);
		j = ft_strlen(cur->content) - 1;
		while (j <= vars->map.width - 1)
		{
			vars->map.arr[i][j] = ' ';
			j++;
		}
		i++;
		cur = cur->next;
	}
}

void	set_map(t_vars *vars, int fd, char *line)
{
	t_list	*head;
	t_list	*tmp;

	head = ft_lstnew(line);
	vars->map.height++;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, "\n", 1))
			print_error("Invalid map: new line", vars);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
		vars->map.height++;
		if (vars->map.width < ft_strlen(line) - 1)		// 개행 제거한 길이가 map 의 width 
			vars->map.width = ft_strlen(line) - 1;
	}
	init_map_arr(vars, head);
	print_arr_2d(vars->map.arr);
//	print_lst(head);
}
