/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:55:45 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/28 00:01:27 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h> //, time rand()
#include <sys/time.h>

int		random_generator(int frequency)
{
    struct timeval      tv;
    unsigned long long  milliseconds;
    int                 ret;

    gettimeofday(&tv, NULL);
    milliseconds = (unsigned long long)(tv.tv_usec);
    srand((unsigned int)milliseconds);
    ret = rand();
    if (ret % frequency == 0)
        return (1);
    return (0);
}

void    *ft_malloc(size_t size)
{
    void    *bass;

    bass = malloc(size);
    if (bass == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return (bass);
}

int ft_open(char *file_path)
{
    int fd;

    fd = open(file_path, O_RDONLY, 0600);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return (fd);
}

void	vars_free(t_vars *vars)
{
    if (vars->info)
    {
        for (int i = 0; i < TEX_NUM; i++)
            free(vars->info->texture[i]);
        free(vars->info->texture);
        free(vars->info);
    }
    if (vars->sprite)
        free (vars->sprite);
}

int	exit_game(t_vars *vars)
{
	write(1, "Player has exited the game\n", 27);
	//mlx_destroy_window(vars->mlx, vars->win);
	vars_free(vars);
	exit(EXIT_SUCCESS);
}
