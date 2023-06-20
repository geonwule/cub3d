/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:24:24 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/09 11:25:20 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//execve
#include <unistd.h>

//exit
#include <stdlib.h>

//perror
#include <stdio.h>

void	ft_execve(char *filepath, char **argv, char **envp)
{
	if (execve(filepath, argv, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}