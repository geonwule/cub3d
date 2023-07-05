/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:15:09 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 20:14:57 by jonchoi          ###   ########.fr       */
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
		while (rgb[i][j])
		{
			if (!ft_strchr("0123456789+-\n", rgb[i][j]) \
				|| rgb[2][0] == '\n')
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
			return (1);
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
	char	**rgb;
	int		errno;

	errno = 0;
	if (count_rest_point(arr) != 2)
		return (1);
	rgb = ft_split(arr[1], ',');
	if (size_arr_2d(rgb) != 3 || check_digit_rgb(rgb) \
		||process_set_rgb(vars, rgb, type))
		errno = 1;
	free_arr_2d(&rgb);
	if (errno)
		return (1);
	return (0);
}

int	set_color(char **arr, t_vars *vars)
{
	if (!ft_strcmp(arr[0], "F"))
	{
		if (vars->map.info.floor)
			return (1);
		vars->map.info.floor = allocate_and_copy_string(arr[1]);
		if (set_rgb(arr, vars, 'F'))
			return (1);
	}
	else if (!ft_strcmp(arr[0], "C"))
	{
		if (vars->map.info.ceiling)
			return (1);
		vars->map.info.ceiling = allocate_and_copy_string(arr[1]);
		if (set_rgb(arr, vars, 'C'))
			return (1);
	}
	return (0);
}
