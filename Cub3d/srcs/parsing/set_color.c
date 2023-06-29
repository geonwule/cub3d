/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:15:09 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/29 21:25:25 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_digit_rgb(char **rgb)
{
	int i;
	int j;

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

int	ft_atoi_color(const char *str)
{
	int	i;
	int	flag;
	int	result;

	i = 0;
	result = 0;
	flag = 1;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	if (flag == -1 || str[i] == '+' || str[i] == '-')
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (result / 1000)
			return (-1);
		i++;
	}
	result *= flag;
	return (result);
}

int	set_rgb(char **arr, t_vars *vars, char type)
{
	int		i;
	int		cnt;
	char	**rgb;
	int		tmp;

	i = 0;
	cnt = 0;
	while (arr[1][i])
	{
		if (arr[1][i] == ',')
			cnt++;
		i++;
	}
	if (cnt != 2)
		return (1);
	rgb = ft_split(arr[1], ',');
	if (size_arr_2d(rgb) != 3)
	{
		free_arr_2d(&rgb);
		return (1);
	}
	if (check_digit_rgb(rgb))
	{
		free_arr_2d(&rgb);
		return (1);
	}
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
	free_arr_2d(&rgb);
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
