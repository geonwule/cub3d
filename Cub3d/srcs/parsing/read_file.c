/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:42:31 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/25 01:31:28 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_file(t_vars *vars, char *path)
{
	int len;

	len = ft_strlen(path);
	if (len < 5)
		print_error("Invaild file name", vars);
	if (path[len - 1] != 'b' || path[len - 2] != 'u' \
		|| path[len - 3] != 'c' || path[len - 4] != '.')
		print_error("Invalid file format", vars);
}

// init_map_height();

void	init_map_info(t_vars *vars, char *path)
{
	int		fd;
	char	*line;
	char	**arr;
	int		cnt;

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
		if (set_texture(arr, vars))
			cnt++;
		if (set_color(arr, vars))
			cnt++;
		if (cnt > 5)
		{
//			printf("arr[0]: %s\n", arr[0]);
		}
	
		free_arr_2d(&arr);
		free(line);
	}
}

void	read_file(t_vars *vars, char *path)
{
	check_file(vars, path);
	init_map_info(vars, path);

	/*print test*/
	print_texture(vars);
	print_color(vars);
}
