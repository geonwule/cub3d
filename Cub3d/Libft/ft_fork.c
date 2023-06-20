/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:27:06 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/09 11:27:30 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fork, pid_t <sys/_types/_pid_t.h>
#include <unistd.h>

//perror
#include <stdio.h>

//exit
#include <stdlib.h>

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}