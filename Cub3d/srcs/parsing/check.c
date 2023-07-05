/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:56:22 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 15:59:48 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(t_vars *vars, char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		print_error("Invaild file name", vars);
	if (path[len - 1] != 'b' || path[len - 2] != 'u' \
		|| path[len - 3] != 'c' || path[len - 4] != '.')
		print_error("Invalid file format", vars);
}

int	check_texture(char *line)
{
	char	**arr;
	int		end;

	arr = ft_split(line, ' ');
	if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])) \
			|| !ft_strncmp(arr[0], "SO", ft_strlen(arr[0])) \
			|| !ft_strncmp(arr[0], "WE", ft_strlen(arr[0])) \
			|| !ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
	{
		if (line[0] == ' ')
		{
			free_arr_2d(&arr);
			return (0);
		}
		end = (int)ft_strlen(arr[1]) - 1;
		if (arr[1][end] != '\n')
		{
			free_arr_2d(&arr);
			return (0);
		}
		free_arr_2d(&arr);
		return (1);
	}
	free_arr_2d(&arr);
	return (0);
}

int	check_color(char *line)
{
	char	**arr;
	int		end;

	arr = ft_split(line, ' ');
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0]))
		|| !ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if (line[0] == ' ')
		{
			free_arr_2d(&arr);
			return (0);
		}
		end = (int)ft_strlen(arr[1]) - 1;
		if (arr[1][end] != '\n')
		{
			free_arr_2d(&arr);
			return (0);
		}
		free_arr_2d(&arr);
		return (1);
	}
	free_arr_2d(&arr);
	return (0);
}
