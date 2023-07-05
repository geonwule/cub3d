/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:30:34 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/06 00:27:35 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(char **arr, t_vars *vars)
{
	if (!ft_strcmp(arr[0], "NO"))
	{
		if (vars->map.info.north)
			return (1);
		vars->map.info.north = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strcmp(arr[0], "SO"))
	{
		if (vars->map.info.south)
			return (1);
		vars->map.info.south = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strcmp(arr[0], "WE"))
	{
		if (vars->map.info.west)
			return (1);
		vars->map.info.west = allocate_and_copy_string(arr[1]);
	}
	else if (!ft_strcmp(arr[0], "EA"))
	{
		if (vars->map.info.east)
			return (1);
		vars->map.info.east = allocate_and_copy_string(arr[1]);
	}
	return (0);
}

static void	init_map_arr(t_vars *vars, t_list *head)
{
	int		i;
	int		j;
	t_list	*cur;
	char	*str;

	vars->map.arr = (char **)ft_malloc(sizeof(char *) * (vars->map.height + 1));
	vars->map.arr[vars->map.height] = NULL;
	i = 0;
	cur = head;
	while (cur)
	{
		vars->map.arr[i] = (char *)ft_malloc(sizeof(char) * vars->map.width);
		str = (char *)cur->content;
		if (str[(int)ft_strlen(cur->content) - 1] == '\n')
			ft_memcpy(vars->map.arr[i], cur->content, \
					ft_strlen(cur->content) - 1);
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

static void	process_set_map(t_vars *vars, char *line, t_list *head)
{
	t_list	*tmp;

	tmp = ft_lstnew(line);
	ft_lstadd_back(&head, tmp);
	vars->map.height++;
	if (vars->map.width < (int)ft_strlen(line) - 1)
		vars->map.width = ft_strlen(line) - 1;
}

int	set_map(t_vars *vars, int fd, char *line)
{
	t_list	*head;
	int		errno;

	errno = 0;
	head = ft_lstnew(line);
	vars->map.height++;
	if (vars->map.width < (int)ft_strlen(line) - 1)
		vars->map.width = ft_strlen(line) - 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
		{
			errno = 2;
			break ;
		}
		process_set_map(vars, line, head);
	}
	init_map_arr(vars, head);
	free_lst(&head);
	return (errno);
}
