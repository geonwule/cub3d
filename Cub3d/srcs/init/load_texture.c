/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 03:09:59 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/05 03:23:30 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_image(t_vars *vars, int *texture, char *path, t_img *img)
{
	int	i;
	int	j;

	img->img = ft_xpm_file_to_image(vars->mlx, path, &img->img_width, \
								&img->img_height);
	img->data = (int *)ft_get_data_addr(img->img, &img->bpp, \
								&img->size_l, &img->endian);
	i = 0;
	while (i < img->img_height)
	{
		j = 0;
		while (j < img->img_width)
		{
			texture[img->img_width * i + j] = img->data[img->img_width * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(vars->mlx, img->img);
}

void	load_texture(t_vars *vars, t_info *info)
{
	t_img	img;

	load_image(vars, info->texture[TEX_NO], vars->map.info.north, &img);
	load_image(vars, info->texture[TEX_SO], vars->map.info.south, &img);
	load_image(vars, info->texture[TEX_EA], vars->map.info.east, &img);
	load_image(vars, info->texture[TEX_WE], vars->map.info.west, &img);
	load_image(vars, info->texture[TEX_DOOR], R_DOOR, &img);
	load_image(vars, info->texture[TEX_MONSTER], R_MONSTER, &img);
	load_image(vars, info->texture[TEX_POTION], R_POTION, &img);
	load_image(vars, info->texture[TEX_NPC], R_NPC, &img);
}
