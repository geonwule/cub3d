/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:56:22 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/28 04:28:09 by jonchoi          ###   ########.fr       */
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

int	check_texture(char **arr)
{
	if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])) \
			|| !ft_strncmp(arr[0], "SO", ft_strlen(arr[0])) \
			|| !ft_strncmp(arr[0], "WE", ft_strlen(arr[0])) \
			|| !ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
		return (1);
	return (0);
}

int	check_color(char **arr)
{
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0]))
		|| !ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
		return (1);
	return (0);
}
