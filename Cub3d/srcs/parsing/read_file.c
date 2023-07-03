/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:01:36 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/03 20:08:39 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_info(t_vars *vars, char *path)
{
	int		fd;
	char	*line;
	char	**arr;
	int		cnt;
	int		errno;

	errno = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("File open failed", vars);
	cnt = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		arr = ft_split(line, ' ');
		if (cnt < 6 && ft_strncmp(line, "\n", 1)
			&& !check_texture(arr) && !check_color(arr))
		{
			free_arr_2d(&arr);
			print_error("Invalid info input 1", vars);
		}
		if (check_texture(arr))
		{
			errno = set_texture(arr, vars);
			cnt++;
		}
		else if (check_color(arr))
		{
			errno = set_color(arr, vars);
			cnt++;
		}
		else if (cnt == 6 && ft_strncmp(line, "\n", 1))
		{
			free_arr_2d(&arr);
			set_map(vars, fd, line);
			break ;
		}
		free_arr_2d(&arr);
		free(line);
		if (errno)
			print_error("Invalid info input 2", vars);
	}
}

void	read_file(t_vars *vars, char *path)
{
	vars->map.height = 0;
	vars->map.width = 0;
	vars->map.info.north = NULL;
	vars->map.info.south = NULL;
	vars->map.info.west = NULL;
	vars->map.info.east = NULL;
	vars->map.info.floor = NULL;
	vars->map.info.ceiling = NULL;
	vars->map.arr = NULL;
	check_file(vars, path);
	init_map_info(vars, path);
	if (check_map(vars))
		print_error("Invalid map", vars);
	vars->data.init_pos[X] = vars->info->posX;
	vars->data.init_pos[Y] = vars->info->posY;
	vars->data.init_dir[X] = vars->info->dirX;
	vars->data.init_dir[Y] = vars->info->dirY;
	vars->data.init_plane[X] = vars->info->planeX;
	vars->data.init_plane[Y] = vars->info->planeY;
	/*print test*/
//	print_texture(vars);
//	print_color(vars);
//	print_arr_2d(vars->map.arr);
}
