/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:01:36 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/28 00:37:57 by jonchoi          ###   ########.fr       */
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
			printf("errno: %d\n", errno);	//print
			cnt++;
		}
		else if (!errno && cnt == 6 && ft_strncmp(line, "\n", 1))
		{
			printf("Go func set_map arr\n");		// del
			free_arr_2d(&arr);
			set_map(vars, fd, line);
			break ;
		}
		free_arr_2d(&arr);
		free(line);
		if (errno)
			print_error("Too many argument", vars);
	}
}

void	read_file(t_vars *vars, char *path)
{
	check_file(vars, path);
	init_map_info(vars, path);

	/*print test*/
	print_texture(vars);
	print_color(vars);
	print_arr_2d(vars->map.arr);
}
