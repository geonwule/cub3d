/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 03:10:49 by jonchoi           #+#    #+#             */
/*   Updated: 2023/07/17 12:54:34 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_init_vars_info1(t_vars *vars, t_info *info)
{
	info->pos_x = vars->data.init_pos[X];
	info->pos_y = vars->data.init_pos[Y];
	info->dir_x = vars->data.init_dir[X];
	info->dir_y = vars->data.init_dir[Y];
	info->plane_x = vars->data.init_plane[X];
	info->plane_y = vars->data.init_plane[Y];
	info->move_speed = 0.05;
	info->rot_speed = 0.03;
}

static void	process_init_vars_info2(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	process_init_vars_info3(t_vars *vars, t_info *info)
{
	int	i;
	int	j;

	info->texture = (int **)ft_malloc(sizeof(int *) * TEX_NUM);
	i = 0;
	while (i < TEX_NUM)
	{
		info->texture[i] = (int *)ft_malloc(sizeof(int) * \
							TEX_WIDTH * TEX_HEIGHT);
		j = 0;
		while (j < TEX_HEIGHT)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	load_texture(vars, info);
}

int	init_vars_info(t_vars *vars)
{
	t_info	*info;

	info = &vars->info;
	process_init_vars_info1(vars, info);
	process_init_vars_info2(info);
	process_init_vars_info3(vars, info);
	info->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	info->img.data = (int *)ft_get_data_addr(info->img.img, &info->img.bpp, \
					&info->img.size_l, &info->img.endian);
	img_xpm_set(vars);
	mlx_mouse_hide();
	return (RETURN_SUCCESS);
}
