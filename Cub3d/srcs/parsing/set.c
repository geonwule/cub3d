/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:30:34 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/03 16:52:36 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		i;
	int		j;
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
	int		errno;

	errno = 0;
	head = ft_lstnew(line);
	vars->map.height = 0;

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
		if (vars->map.width < ft_strlen(line) - 1)
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
