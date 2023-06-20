/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:11:38 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/04 18:11:49 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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