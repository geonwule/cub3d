/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:01:13 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/03 16:26:01 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vars_allocation(t_vars *vars)
{
	t_info	*info;
	int		i;

	info = ft_malloc(sizeof(t_info));
	vars->info = info;

	vars->data.monster_come = 0;
	vars->data.m_num = 0;
	vars->data.warning_time = 0;
	vars->sprite.sp = NULL;

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

	vars->sprite.v_move = 64;
	vars->sprite.v_i = 20;

	vars->data.mouse_x = WIN_WIDTH / 2;
	vars->data.mouse_old_x = WIN_WIDTH / 2;
	vars->data.mouse_y = WIN_HEIGHT / 2;

	vars->data.render_i = 0;
	i = -1;
	while (++i < 1000)
		vars->data.keyboard[i] = 0;
}

static void	img_xpm_set(t_vars *vars)
{
	int	x;
	int	y;

	vars->mini.player_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/player_10.xpm", &x, &y);
	vars->mini.empty_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/empty_10.xpm", &x, &y);
	vars->mini.wall_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/wall_10.xpm", &x, &y);
	vars->mini.monster_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/monster_10.xpm", &x, &y);
	vars->mini.door_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/door_10.xpm", &x, &y);
	vars->mini.potion_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/potion_10.xpm", &x, &y);
	vars->mini.dir_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/dir_10.xpm", &x, &y);
	vars->mini.npc_x = ft_xpm_file_to_image(vars->mlx, "./texture/minimap/npc.xpm", &x, &y);

	vars->xpm.quest_start = ft_xpm_file_to_image(vars->mlx, "./texture/npc/quest_start.xpm", &x, &y);
	vars->xpm.quest_ing = ft_xpm_file_to_image(vars->mlx, "./texture/npc/quest_ing.xpm", &x, &y);
	vars->xpm.quest_end = ft_xpm_file_to_image(vars->mlx, "./texture/npc/quest_end.xpm", &x, &y);
	
	vars->xpm.dead = ft_xpm_file_to_image(vars->mlx, "texture/etc/dead.xpm", &x, &y);
	vars->xpm.damage = ft_xpm_file_to_image(vars->mlx, "texture/etc/damage.xpm", &x, &y);
	vars->xpm.aim = ft_xpm_file_to_image(vars->mlx, "texture/etc/aim.xpm", &x, &y);
	vars->xpm.w_messege = ft_xpm_file_to_image(vars->mlx, "texture/etc/warning.xpm", &x, &y);
	vars->xpm.hand1 = ft_xpm_file_to_image(vars->mlx, "texture/etc/hand1.xpm", &x, &y);
	vars->xpm.hand2 = ft_xpm_file_to_image(vars->mlx, "texture/etc/hand2.xpm", &x, &y);

	vars->xpm.hp1 = ft_xpm_file_to_image(vars->mlx, "texture/underbar/hp1.xpm", &x, &y);
	vars->xpm.hp2 = ft_xpm_file_to_image(vars->mlx, "texture/underbar/hp2.xpm", &x, &y);
	vars->xpm.hp3 = ft_xpm_file_to_image(vars->mlx, "texture/underbar/hp3.xpm", &x, &y);
	vars->xpm.exp1 = ft_xpm_file_to_image(vars->mlx, "texture/underbar/exp1.xpm", &x, &y);
	vars->xpm.exp2 = ft_xpm_file_to_image(vars->mlx, "texture/underbar/exp2.xpm", &x, &y);
	vars->xpm.lv = ft_xpm_file_to_image(vars->mlx, "texture/underbar/level.xpm", &x, &y);
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

#ifdef DEBUG_MON
#include <string.h>
#endif

static void	load_image(t_vars *vars, t_info *info, int *texture, char *path, t_img *img)
{
	img->img = ft_xpm_file_to_image(vars->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)ft_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);

	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			#ifdef DEBUG_MON
			printf("%d", texture[img->img_width * y + x]);
			if (x % img->img_width == 0)
				printf("\n");
			#endif
		}
	}
	#ifdef DEBUG_MON
	printf("exit\n");
	exit(0);
	#endif
	mlx_destroy_image(vars->mlx, img->img);
}

static void	load_texture(t_vars *vars, t_info *info)
{
	t_img	img;
	load_image(vars, info, info->texture[TEX_NO], vars->map.info.north, &img);
	load_image(vars, info, info->texture[TEX_SO], vars->map.info.south, &img);
	load_image(vars, info, info->texture[TEX_EA], vars->map.info.east, &img);
	load_image(vars, info, info->texture[TEX_WE], vars->map.info.west, &img);
	load_image(vars, info, info->texture[TEX_DOOR], "texture/ray/door.xpm", &img);
	load_image(vars, info, info->texture[TEX_MONSTER], "texture/ray/monster.xpm", &img);
	load_image(vars, info, info->texture[TEX_POTION], "texture/ray/potion.xpm", &img);
	load_image(vars, info, info->texture[TEX_NPC], "texture/npc/npc.xpm", &img);
}

int vars_init(t_vars *vars)
{
	t_info	*info = vars->info;

	info->posX = vars->data.init_pos[X];
	info->posY = vars->data.init_pos[Y];
	info->dirX = vars->data.init_dir[X];
	info->dirY = vars->data.init_dir[Y];
	info->planeX = vars->data.init_plane[X];
	info->planeY = vars->data.init_plane[Y];	
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.08;

	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			info->buf[y][x] = 0;
		}
	}
	//texture 8개
	info->texture = (int **)ft_malloc(sizeof(int *) * TEX_NUM);
	for (int i = 0; i < TEX_NUM; i++)
	{
		info->texture[i] = (int *)ft_malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		for (int j = 0; j < TEX_HEIGHT * TEX_WIDTH; j++)
		{
			info->texture[i][j] = 0;
		}
	}
	load_texture(vars, info);
	info->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	info->img.data = (int *)ft_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
    img_xpm_set(vars);
    return (RETURN_SUCCESS);
}
