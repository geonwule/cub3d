/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:28:55 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/15 14:16:33 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13)) // white_space
		return (1);
	return (0);
}

static int is_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n' && is_space(line[i])) //if_only_space?
		i++;
	if (!(line[i] == '\0' && line[i] == '\n')) //is_not_only_space
		return (0);
	return (1);
}

// static int	is_map(char *line, t_vars *vars)
// {
// 	int		i;

// 	i = 0;
// 	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' \
// 		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
// 		return (0);
// 	while (line[i] != '\0' && line[i] !='\n')
// 	{
// 		if (line[i] == 'N' || line[i] == 'W' \
// 			|| line[i] == 'S' || line[i] == 'E')
// 		{
// 			vars->info->posX = i;
// 			vars->info->posY = vars->map->height;
// 			printf("x = %f\ny = %f\n", vars->info->posX, vars->info->posY);
// 			exit(0);
// 		}
// 		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'W' \
// 			|| line[i] == 'S' || line[i] == 'E' || is_space(line[i])))
// 			return (-1);
// 		i++;
// 	}

// 	t_map	*map = vars->map;
// 	int		temp_width = ft_strlen(line) - 1;
// 	if (map->width < temp_width)
// 		map->width = temp_width;
// 	map->height++;

// 	return (1);
// }


static int	is_texture(char *line, t_vars *vars)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		vars->north = ft_strdup("\"");
		char *temp = ft_substr(line, 3, ft_strlen(&line[3]) - 1);
		vars->north = ft_strjoin_gnl(vars->north, temp);
		free(temp);
		vars->north = ft_strjoin_gnl(vars->north, "\"");
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
		vars->south = ft_strdup(&line[3]);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		vars->west = ft_strdup(&line[3]);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		vars->east = ft_strdup(&line[3]);
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		vars->floor = ft_strdup(&line[2]);
		vars->f[0] = 220;	// modify
		vars->f[1] = 100;
		vars->f[2] = 0;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		vars->ceiling = ft_strdup(&line[2]);
		vars->c[0] = 225;	// modify
		vars->c[1] = 30;
		vars->c[2] = 0;
	}
	else
		return (0);
	return (1);
}

int	map_read(char *map_path, t_vars *vars)
{
    // int     fd;
    // char    *line;
    
    // fd = ft_open(map_path);
    // line = get_next_line(fd);
    // while (line)
    // {
	// 	int status;
	// 	if (is_only_space(line))
	// 	{
	// 		if (line)
	// 			free(line);
	// 		line = get_next_line(fd);
	// 		continue ;
	// 	}
	// 	status = is_map(line, vars);  // line strjoin, map
    //     if (status < 0)
	// 	{
	// 		close(fd);
	// 		if (line)
	// 			free(line);
	// 		printf("is_map_error\n");//tmp
	// 		return (RETURN_FAILURE);
	// 	}
	// 	else if (status)
	// 	{
	// 		if (line)
	// 			free(line);
	// 		line = get_next_line(fd);
    //         continue ;
	// 	}
    //     if (!is_texture(line, vars))
	// 	{
	// 		close(fd);
	// 		if (line)
	// 			free(line);
    //         return (RETURN_FAILURE);
	// 	}
	// 	if (line)
	// 		free(line);
    //     line = get_next_line(fd);
    // }

	// #ifdef DEBUG
	// printf("map_height = %d\nmap_width = %d\n", vars->map->height, vars->map->width);
	// for (int i = 0; i < vars->map->height; i++)
	// 	printf("%s\n", vars->map->arr[i]);
	// exit(0);
	
	// printf("NO = %s\n",vars->north);
	// printf("SOUTH = %s\n",vars->south);
	// printf("EAST = %s\n",vars->east);
	// printf("WEST = %s\n",vars->west);
	// printf("FLOO = %s\n",vars->floor);
	// printf("CEI = %s\n",vars->ceiling);
	// #endif
	
	// if (line)
	// 	free(line);
    // close(fd);
	
    return (RETURN_SUCCESS);
}
