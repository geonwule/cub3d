/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:15:09 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/03 23:15:16 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_digit_rgb(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb[i][j] && rgb[i][j] != '\n')
		{
			if (!ft_isdigit(rgb[i][j]) && !ft_strchr("+-", rgb[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	process_set_rgb(t_vars *vars, char **rgb, char type)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < 3)
	{
		tmp = ft_atoi_color(rgb[i]);
		if (tmp < 0 || tmp > 255)
		{
			free_arr_2d(&rgb);
			return (1);
		}
		if (type == 'F')
			vars->map.info.f[i] = tmp;
		else if (type == 'C')
			vars->map.info.c[i] = tmp;
		i++;
	}
	return (0);
}

static int	count_rest_point(char **arr)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (arr[1][i])
	{
		if (arr[1][i] == ',')
			cnt++;
		i++;
	}
	return (cnt);
}

static int	set_rgb(char **arr, t_vars *vars, char type)
{
	int		i;
	char	**rgb;
	int		errno;

	errno = 0;
	if (count_rest_point(arr) != 2)
		return (1);
	rgb = ft_split(arr[1], ',');
	if (size_arr_2d(rgb) != 3)
		errno = 1;
	errno = check_digit_rgb(rgb);
	errno = process_set_rgb(vars, rgb, type);
	if (errno)
	{
		free_arr_2d(&rgb);
		return (1);
	}
	return (0);
}

int	set_color(char **arr, t_vars *vars)
{
	char	**rgb;

	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		if (vars->map.info.floor)
			return (1);
		vars->map.info.floor = allocate_and_copy_string(arr[1], vars);
		if (set_rgb(arr, vars, 'F'))
			return (1);
	}
	else if (!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if (vars->map.info.ceiling)
			return (1);
		vars->map.info.ceiling = allocate_and_copy_string(arr[1], vars);
		if (set_rgb(arr, vars, 'C'))
			return (1);
	}
	return (0);
}
