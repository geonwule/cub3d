/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:42:31 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/25 06:19:39 by jonchoi          ###   ########.fr       */
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

static int	check_texture(char **arr)
{
		if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])) 
			|| !ft_strncmp(arr[0], "SO", ft_strlen(arr[0]))
			|| !ft_strncmp(arr[0], "WE", ft_strlen(arr[0]))
			|| !ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
			return (1);
		return (0);
}

static int	check_color(char **arr)
{
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0]))
		|| !ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
		return (1);
	return (0);
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
		if (cnt < 6 && ft_strncmp(line, "\n", 1)
			&& !check_texture(arr) && !check_color(arr))
			print_error("Invalid info input 1", vars);
		if (cnt >= 6 && ft_strncmp(line, "\n", 1))
		{
			printf("func set_map arr\n");
			set_map(arr, vars, fd, line);
			break ;
		}

		if (check_texture(arr))
		{
			set_texture(arr, vars);
			cnt++;
		}
		else if (check_color(arr))
		{
			set_color(arr, vars);
			cnt++;
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
