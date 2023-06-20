/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:43 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/09 11:28:26 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pipe
#include <unistd.h>

//perror
#include <stdio.h>

//exit
#include <stdlib.h>

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}