/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:19:00 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:21:54 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_get_data_addr(void *img_ptr, int *bits, int *size, int *end)
{
	char	*data;

	data = mlx_get_data_addr(img_ptr, bits, size, end);
	if (data == NULL)
	{
		printf("Error\n");
		printf("mlx_get_data_addr: img_ptr not exist\n");
		exit(EXIT_FAILURE);
	}
	return (data);
}
