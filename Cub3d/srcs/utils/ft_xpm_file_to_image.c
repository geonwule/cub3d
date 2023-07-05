/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpm_file_to_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:22:14 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 11:24:16 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_xpm_file_to_image(void *mlx_ptr, char *path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx_ptr, path, w, h);
	if (img == NULL)
	{
		printf("Error\n");
		printf("mlx_xpm_file_to_image: %s not exist\n", path);
		exit(EXIT_FAILURE);
	}
	return (img);
}
