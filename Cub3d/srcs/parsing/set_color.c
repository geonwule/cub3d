/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:15:09 by jonchoi           #+#    #+#             */
/*   Updated: 2023/06/28 01:52:14 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_rgb(char **arr, t_vars *vars, char type)
{
	int		i;
	int		cnt;
	char	**rgb;

	i = 0;
	cnt = 0;
	while (arr[1][i])
	{
		if (arr[1][i] == ',')
			cnt++;
		i++;
	}
	if (cnt > 2)
		return (1);
	rgb = ft_split(arr[1], ',');
	if (size_arr_2d(rgb) != 3)
		return (1);
	i = 0;
	int tmp;
	while (i < 3)
	{
		tmp = ft_atoi(rgb[i]);
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

int	set_color(char **arr, t_vars *vars)
{
	char **rgb;

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
