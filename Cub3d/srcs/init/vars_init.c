/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:01:13 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/20 17:49:43 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern char	map[15][34]; //tmp

t_vars  *vars_allocation(void)
{
    t_vars  *vars;
	// t_map	*map;
	t_info	*info;
	int		i;

    vars = malloc(sizeof(t_vars));
	// map	= malloc(sizeof(t_map));
	info = malloc(sizeof(t_info));
	vars->info = info;
    vars->north = NULL;
    vars->south = NULL;
    vars->west = NULL;
    vars->east = NULL;
    vars->floor = NULL;
    vars->ceiling = NULL;
	vars->monster_come = 0;
	// map->height = 0;
	// map->width = 0;
	// map->arr = NULL;
	// map->tmp_arr = NULL;
	// vars->map = map;
	i = -1;
	while (++i < 1000)
		vars->keyboard[i] = 0;
    return (vars);
}

static void	img_xpm_set(t_vars *vars)
{
	int	x;
	int	y;

	// vars->north_x = mlx_xpm_file_to_image(vars->mlx, vars->north, &x, &y);
	// vars->south_x = mlx_xpm_file_to_image(vars->mlx, vars->south, &x, &y);
	// vars->east_x = mlx_xpm_file_to_image(vars->mlx, vars->east, &x, &y);
	// vars->west_x = mlx_xpm_file_to_image(vars->mlx, vars->west, &x, &y);
	vars->north_x = mlx_xpm_file_to_image(vars->mlx, NORTH, &x, &y);
	vars->south_x = mlx_xpm_file_to_image(vars->mlx, SOUTH, &x, &y);
	vars->east_x = mlx_xpm_file_to_image(vars->mlx, EAST, &x, &y);
	vars->west_x = mlx_xpm_file_to_image(vars->mlx, WEST, &x, &y);
	vars->player_x = mlx_xpm_file_to_image(vars->mlx, PLAYER, &x, &y);
	vars->empty_x = mlx_xpm_file_to_image(vars->mlx, EMPTY, &x, &y);
	vars->wall_x = mlx_xpm_file_to_image(vars->mlx, WALL, &x, &y);
}

void	set_dir(t_info *info, double x, double y)
{
	info->dirX = x;
	info->dirY = y;
}

void	set_plane(t_info *info, double x, double y)
{
	info->planeX = x;
	info->planeY = y;
}

static void	load_image(t_vars *vars, t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(vars->mlx, img->img);
}

static void	load_texture(t_vars *vars, t_info *info)
{
	t_img	img;
	load_image(vars, info, info->texture[TEX_NO], "texture/north.xpm", &img);
	load_image(vars, info, info->texture[TEX_SO], "texture/south.xpm", &img);
	load_image(vars, info, info->texture[TEX_EA], "texture/east.xpm", &img);
	load_image(vars, info, info->texture[TEX_WE], "texture/west.xpm", &img);
	load_image(vars, info, info->texture[TEX_MONSTER], "texture/monster.xpm", &img);
	// load_image(vars, info, info->texture[5], "textures_study/mossy.xpm", &img);
	// load_image(vars, info, info->texture[6], "textures_study/wood.xpm", &img);
	// load_image(vars, info, info->texture[7], "textures_study/colorstone.xpm", &img);
}
	// load_image(vars, info, info->texture[TEX_NO], NORTH, &img);
	// load_image(vars, info, info->texture[TEX_SO], SOUTH, &img);
	// load_image(vars, info, info->texture[TEX_EA], EAST, &img);
	// load_image(vars, info, info->texture[TEX_WE], WEST, &img);

int vars_init(t_vars *vars)
{
	t_info	*info = vars->info;
	
	info->posX = 11.0;
	info->posY = 26.0;
	
	//player direction(x, y) 플레이어 방향 벡터
	info->dirX = -1.0;
	info->dirY = 0.0;
	
	//camera line 카메라 평면벡터
	info->planeX = 0.0;
	info->planeY = 0.66;

	info->moveSpeed = 0.04;
	info->rotSpeed = 0.04;

	vars->f[0] = 220;
	vars->f[1] = 100;
	vars->f[2] = 0;
	vars->c[0] = 225;
	vars->c[1] = 30;
	vars->c[2] = 0;

	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			info->buf[y][x] = 0;
		}
	}

	//texture 8개
	info->texture = (int **)malloc(sizeof(int *) * 8);
	for (int i = 0; i < 8; i++)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		for (int j = 0; j < TEX_HEIGHT * TEX_WIDTH; j++)
		{
			info->texture[i][j] = 0;
		}
	}

	load_texture(vars, info);
	info->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
	
	//->rgb
	// vars->img_ptr = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	// vars->data = mlx_get_data_addr(vars->img_ptr, &vars->bpp, &vars->size_l, &vars->endian);
    img_xpm_set(vars);
    return (RETURN_SUCCESS);
}