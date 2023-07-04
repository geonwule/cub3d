/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:01:13 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 19:59:21 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_init_vars1(t_vars *vars)
{
	vars->data.monster_come = 0;
	vars->data.m_num = 0;
	vars->data.warning_time = 0;
	vars->data.hand_change = 0;
	vars->data.hp = 3;
	vars->data.hp_before = 3;
	vars->data.hunt = 0;
	vars->data.level = 1;
	vars->data.dead_check = 0;
	vars->data.m_speed = 0;
	vars->data.npc_talk = 0;
	vars->data.quest_num = 0;
	vars->data.quest_monster_num = 30;
	vars->data.mouse_x = WIN_WIDTH / 2;
	vars->data.mouse_old_x = WIN_WIDTH / 2;
	vars->data.mouse_y = WIN_HEIGHT / 2;
	vars->data.render_i = 0;
}

static void	process_init_vars2(t_vars *vars)
{
	int	i;

	vars->sprite.sp = NULL;
	vars->sprite.v_move = 64;
	vars->sprite.v_i = 20;
	vars->sprite.u_div = 1.5;
	vars->sprite.v_div = 1.5;
	i = 0;
	while (i < 1000)
	{
		vars->data.keyboard[i] = 0;
		i++;
	}
}

void	init_vars(t_vars *vars)
{
	process_init_vars1(vars);
	process_init_vars2(vars);
}

static void	process_img_xpm_set1(t_vars *vars, int x, int y)
{
	vars->mini.player_x = ft_xpm_file_to_image(vars->mlx, M_PLAYER, &x, &y);
	vars->mini.empty_x = ft_xpm_file_to_image(vars->mlx, M_EMPTY, &x, &y);
	vars->mini.wall_x = ft_xpm_file_to_image(vars->mlx, M_WALL, &x, &y);
	vars->mini.monster_x = ft_xpm_file_to_image(vars->mlx, M_MONSTER, &x, &y);
	vars->mini.door_x = ft_xpm_file_to_image(vars->mlx, M_DOOR, &x, &y);
	vars->mini.potion_x = ft_xpm_file_to_image(vars->mlx, M_POTION, &x, &y);
	vars->mini.dir_x = ft_xpm_file_to_image(vars->mlx, M_DIR, &x, &y);
	vars->mini.npc_x = ft_xpm_file_to_image(vars->mlx, M_NPC, &x, &y);
}

static void	process_img_xpm_set2(t_vars *vars, int x, int y)
{
	vars->xpm.quest_start = ft_xpm_file_to_image(vars->mlx, N_QUEST1, &x, &y);
	vars->xpm.quest_ing = ft_xpm_file_to_image(vars->mlx, N_QUEST2, &x, &y);
	vars->xpm.quest_end = ft_xpm_file_to_image(vars->mlx, N_QUEST3, &x, &y);
	vars->xpm.dead = ft_xpm_file_to_image(vars->mlx, E_DEAD, &x, &y);
	vars->xpm.damage = ft_xpm_file_to_image(vars->mlx, E_DAMAGE, &x, &y);
	vars->xpm.aim = ft_xpm_file_to_image(vars->mlx, E_AIM, &x, &y);
	vars->xpm.w_messege = ft_xpm_file_to_image(vars->mlx, E_WARNING, &x, &y);
	vars->xpm.hand1 = ft_xpm_file_to_image(vars->mlx, E_HAND1, &x, &y);
	vars->xpm.hand2 = ft_xpm_file_to_image(vars->mlx, E_HAND2, &x, &y);
	vars->xpm.hp1 = ft_xpm_file_to_image(vars->mlx, U_HP1, &x, &y);
	vars->xpm.hp2 = ft_xpm_file_to_image(vars->mlx, U_HP2, &x, &y);
	vars->xpm.hp3 = ft_xpm_file_to_image(vars->mlx, U_HP3, &x, &y);
	vars->xpm.exp1 = ft_xpm_file_to_image(vars->mlx, U_EXP1, &x, &y);
	vars->xpm.exp2 = ft_xpm_file_to_image(vars->mlx, U_EXP2, &x, &y);
	vars->xpm.lv = ft_xpm_file_to_image(vars->mlx, U_LEVEL, &x, &y);
}

static void	img_xpm_set(t_vars *vars)
{
	process_img_xpm_set1(vars, 0, 0);
	process_img_xpm_set2(vars, 0, 0);
}

static void	load_image(t_vars *vars, t_info *info, int *texture, char *path, t_img *img)
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

static void	load_texture(t_vars *vars, t_info *info)
{
	t_img	img;

	load_image(vars, info, info->texture[TEX_NO], vars->map.info.north, &img);
	load_image(vars, info, info->texture[TEX_SO], vars->map.info.south, &img);
	load_image(vars, info, info->texture[TEX_EA], vars->map.info.east, &img);
	load_image(vars, info, info->texture[TEX_WE], vars->map.info.west, &img);
	load_image(vars, info, info->texture[TEX_DOOR], R_DOOR, &img);
	load_image(vars, info, info->texture[TEX_MONSTER], R_MONSTER, &img);
	load_image(vars, info, info->texture[TEX_POTION], R_POTION, &img);
	load_image(vars, info, info->texture[TEX_NPC], R_NPC, &img);
}

static void	process_init_vars_info1(t_vars *vars, t_info *info)
{
	info->posX = vars->data.init_pos[X];
	info->posY = vars->data.init_pos[Y];
	info->dirX = vars->data.init_dir[X];
	info->dirY = vars->data.init_dir[Y];
	info->planeX = vars->data.init_plane[X];
	info->planeY = vars->data.init_plane[Y];
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.08;
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


int init_vars_info(t_vars *vars)
{
	t_info	*info;
	
	info = &vars->info;
	process_init_vars_info1(vars, info);
	process_init_vars_info2(info);
	process_init_vars_info3(vars, info);
	info->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	info->img.data = (int *)ft_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
    img_xpm_set(vars);
    return (RETURN_SUCCESS);
}
