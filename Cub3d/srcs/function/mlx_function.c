/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:22:11 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 05:24:21 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_xpm_file_to_image(void *mlx_ptr, char *path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx_ptr, path, w, h);
	if (img == NULL)
	{
		printf("Error: mlx_xpm_file_to_image :");
		printf("%s not exist\n", path);
		exit(EXIT_FAILURE);
	}
	return (img);
}

char	*ft_get_data_addr(void *img_ptr, int *bits, int *size, int *end)
{
	char	*data;

	data = mlx_get_data_addr(img_ptr, bits, size, end);
	if (data == NULL)
	{
		printf("Error: mlx_get_data_addr :");
		printf("img_ptr not exist\n");
		exit(EXIT_FAILURE);
	}
	return (data);
}
