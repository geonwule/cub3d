/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:30:34 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/28 00:00:00 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *allocate_and_copy_string(char *src, t_vars *vars)
{
    char *dst;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src));
    if (!dst)
	{
		print_error("dst malloc err in allocate_and_copy_string func", vars);		// need vars argu
        exit(1);
    }
    dst[ft_strlen(src) - 1] = '\0';		// ft_strlen(src) - 1 : delete '\n'
    ft_memcpy(dst, src, ft_strlen(src) - 1);
    return (dst);
}

int	set_color(char **arr, t_vars *vars)
{
	char **rgb;

	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		if (vars->map.info.floor)
			return (1);
		vars->map.info.floor = allocate_and_copy_string(arr[1], vars);
//		set_rgb(arr, vars, 'F');
	}
	else if (!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if (vars->map.info.ceiling)
			return (1);
		vars->map.info.ceiling = allocate_and_copy_string(arr[1], vars);
//		set_rgb(arr, vars, 'C');
	}
	return (0);
}

int	set_texture(char **arr, t_vars *vars)
{
	if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
	{
		if (vars->map.info.north)
			return (1);
		vars->map.info.north = allocate_and_copy_string(arr[1], vars);
	}
	else if (!ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
	{
		if (vars->map.info.south)
			return (1);
		vars->map.info.south = allocate_and_copy_string(arr[1], vars);
	}
	else if (!ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
	{
		if (vars->map.info.west)
			return (1);
		vars->map.info.west = allocate_and_copy_string(arr[1], vars);
	}
	else if (!ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
	{
		if (vars->map.info.east)
			return (1);
		vars->map.info.east = allocate_and_copy_string(arr[1], vars);
	}
	return (0);
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

void	free_lst(t_list **head)
{
	t_list *cur;
	t_list *next;

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

void	set_map(t_vars *vars, int fd, char *line)
{
	t_list	*head;
	t_list	*tmp;
	int		errno;

	errno = 0;
	head = ft_lstnew(line);
	vars->map.height++;
	while (1)
	{
 		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, "\n", 1))
		{
			errno = 1;
			break ;
		}
		tmp = ft_lstnew(line);
		ft_lstadd_back(&head, tmp);
		vars->map.height++;
		if (vars->map.width < ft_strlen(line) - 1)		// 개행 제거한 길이가 map 의 width
			vars->map.width = ft_strlen(line) - 1;
	}
	if (errno)
	{
		free_lst(&head);
		print_error("Invalid map: new line", vars);
	}
	init_map_arr(vars, head);
	free_lst(&head);
}
