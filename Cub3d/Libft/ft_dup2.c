/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:23:12 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/09 11:25:38 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//dup2
#include <unistd.h>

//exit
#include <stdlib.h>

//perror
#include <stdio.h>

void	ft_dup2(int fd, int change_fd)
{
	if (dup2(fd, change_fd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}