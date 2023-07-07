/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:06:28 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/07 14:03:25 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_order(int *order, double *dist, int amount)
{
	double	tmp_dist;
	int		tmp_idx;
	int		i;
	int		j;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_dist = dist[j];
				tmp_idx = order[j];
				dist[j] = dist[j + 1];
				order[j] = order[j + 1];
				dist[j + 1] = tmp_dist;
				order[j + 1] = tmp_idx;
			}
		}
	}
}

int	*sort_sprite(t_vars *vars, t_info *info, t_sp *sprite)
{
	double	*dist;
	int		*order;
	int		i;

	order = ft_malloc(sizeof(int) * vars->sprite.sprite_num);
	dist = ft_malloc(sizeof(double) * vars->sprite.sprite_num);
	i = -1;
	while (++i < vars->sprite.sprite_num)
	{
		order[i] = i;
		dist[i] = ((info->pos_x - sprite[i].x) * (info->pos_x - sprite[i].x) \
			+ (info->pos_y - sprite[i].y) * (info->pos_y - sprite[i].y));
	}
	sort_order(order, dist, vars->sprite.sprite_num);
	free(dist);
	return (order);
}

static void	draw_y(t_vars *vars, int tex_num, int x, int *tex)
{
	t_sprite	sprite;
	int			y;
	int			depth;
	int			color;

	sprite = vars->sprite;
	y = sprite.d_start_y;
	while (y < sprite.d_end_y)
	{
		depth = (y - sprite.vm_screen) * 256 \
			- WIN_HEIGHT * 128 + sprite.sp_height * 128;
		tex[Y] = ((depth * TEX_HEIGHT) / sprite.sp_height) / 256;
		color = vars->info.texture[tex_num][TEX_WIDTH * tex[Y] + tex[X]];
		if ((color & 0x00FFFFFF) != 0)
			vars->info.buf[y][x] = color;
		y++;
	}
}

static void	sprite_to_screen(t_vars *vars, int tex_num, int x)
{
	t_sprite	sprite;
	int			tex[2];

	sprite = vars->sprite;
	x = sprite.d_start_x;
	while (x < sprite.d_end_x)
	{
		tex[X] = (int)((256 * (x - (-sprite.sp_width / 2 + sprite.screen_x)) \
				* TEX_WIDTH / sprite.sp_width) / 256);
		if (sprite.trans[Y] > 0 && x > 0 && x < WIN_WIDTH \
			&& sprite.trans[Y] < vars->info.z_buffer[x])
			draw_y(vars, tex_num, x, tex);
		x++;
	}
}

void	calculate_sprite(t_vars *vars, t_info *i, int idx, t_sprite *s)
{
	s->pos[X] = vars->sprite.sp[idx].x - i->pos_x;
	s->pos[Y] = vars->sprite.sp[idx].y - i->pos_y;
	s->inv_det = 1.0 / (i->plane_x * i->dir_y - i->dir_x * i->plane_y);
	s->trans[X] = s->inv_det * (i->dir_y * s->pos[X] - i->dir_x * s->pos[Y]);
	s->trans[Y] = s->inv_det * \
					(-i->plane_y * s->pos[X] + i->plane_x * s->pos[Y]);
	s->screen_x = (int)((WIN_WIDTH / 2) * (1 + s->trans[X] / s->trans[Y]));
	s->vm_screen = (int)(vars->sprite.v_move / s->trans[Y]);
	s->sp_height = (int)fabs((WIN_HEIGHT / s->trans[Y]) / s->v_div);
	s->d_start_y = -s->sp_height / 2 + WIN_HEIGHT / 2 + s->vm_screen;
	if (s->d_start_y < 0)
		s->d_start_y = 0;
	s->d_end_y = s->sp_height / 2 + WIN_HEIGHT / 2 + s->vm_screen;
	if (s->d_end_y >= WIN_HEIGHT)
		s->d_end_y = WIN_HEIGHT - 1;
	s->sp_width = (int)fabs((WIN_HEIGHT / s->trans[Y]) / s->u_div);
	s->d_start_x = -s->sp_width / 2 + s->screen_x;
	if (s->d_start_x < 0)
		s->d_start_x = 0;
	s->d_end_x = s->sp_width / 2 + s->screen_x;
	if (s->d_end_x >= WIN_WIDTH)
		s->d_end_x = WIN_WIDTH - 1;
	sprite_to_screen(vars, vars->sprite.sp[idx].texture, s->d_start_x);
}
