/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:01:36 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 15:14:36 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vars_parsing(t_vars *vars)
{
	vars->map.height = 0;
	vars->map.width = 0;
	vars->map.info.north = NULL;
	vars->map.info.south = NULL;
	vars->map.info.east = NULL;
	vars->map.info.west = NULL;
	vars->map.info.floor = NULL;
	vars->map.info.ceiling = NULL;
	vars->map.arr = NULL;
}

static int	open_file(t_vars *vars, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("File open failed", vars);
	return (fd);
}

static int	process_map_info(t_vars *vars, int *cnt, char *line)
{
	int		errno;
	char	**arr;

	arr = ft_split(line, ' ');
	errno = 0;
	if (*cnt < 6 && ft_strncmp(line, "\n", 1) \
			&& !check_texture(line) && !check_color(line))
	{
		errno = 1;
		return (errno);
	}
	else if (check_texture(line))
	{
		errno = set_texture(arr, vars);
		(*cnt)++;
	}
	else if (check_color(line))
	{
		errno = set_color(arr, vars);
		(*cnt)++;
	}
	return (errno);
}

static void	init_map_info(t_vars *vars, char *path)
{
	int		fd;
	char	*line;
	int		cnt;
	int		errno;

	fd = open_file(vars, path);
	cnt = 0;
	errno = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (cnt == 6 && ft_strncmp(line, "\n", 1)
			&& !check_texture(line) && !check_color(line))
		{
			set_map(vars, fd, line);
			break ;
		}
		errno = process_map_info(vars, &cnt, line);
		free(line);
		if (errno)
			print_error("Invalid info input", vars);
	}
}

void	read_file(t_vars *vars, char *path)
{
	init_vars_parsing(vars);
	check_file(vars, path);
	init_map_info(vars, path);
	if (check_map(vars))
		print_error("Invalid map", vars);
	vars->data.init_pos[X] = vars->info.pos_x;
	vars->data.init_pos[Y] = vars->info.pos_y;
	vars->data.init_dir[X] = vars->info.dir_x;
	vars->data.init_dir[Y] = vars->info.dir_y;
	vars->data.init_plane[X] = vars->info.plane_x;
	vars->data.init_plane[Y] = vars->info.plane_y;
}
