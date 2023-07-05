/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:10:20 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:11:21 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_malloc(size_t size)
{
	void	*bass;

	bass = malloc(size);
	if (bass == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (bass);
}
