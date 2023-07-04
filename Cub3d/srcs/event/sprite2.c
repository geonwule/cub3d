/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:06:28 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 17:22:49 by geonwule         ###   ########.fr       */
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
		dist[i] = ((info->posX - sprite[i].x) * (info->posX - sprite[i].x) \
			+ (info->posY - sprite[i].y) * (info->posY - sprite[i].y));
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
		color = vars->info->texture[tex_num][TEX_WIDTH * tex[Y] + tex[X]];
		if ((color >> 24) == 0)
			vars->info->buf[y][x] = color;
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
			&& sprite.trans[Y] < vars->info->zBuffer[x])
			draw_y(vars, tex_num, x, tex);
		x++;
	}
}

void	calculate_sprite(t_vars *vars, t_info *i, int idx, t_sprite *s)
{
	s->pos[X] = vars->sprite.sp[idx].x - i->posX;
	s->pos[Y] = vars->sprite.sp[idx].y - i->posY;
	s->inv_det = 1.0 / (i->planeX * i->dirY - i->dirX * i->planeY);
	s->trans[X] = s->inv_det * (i->dirY * s->pos[X] - i->dirX * s->pos[Y]);
	s->trans[Y] = s->inv_det * (-i->planeY * s->pos[X] + i->planeX * s->pos[Y]);
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


/* 주석 포함
void calculate_sprite(t_vars *vars, int idx, t_sprite *sprite)
{
	t_info *info = vars->info;
	t_sp *sp = vars->sprite.sp; 

	sprite->pos[X] = sp[idx].x - info->posX;
	sprite->pos[Y] = sp[idx].y - info->posY;

	// transform sprite with the inverse camera matrix
	//  [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	//  [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	//  [ planeY   dirY ]                                          [ -planeY  planeX ]

	//inv_det = inverse determinant(역행렬 : 스프라이트 변환에 필요, 카메라 시점에서 상대적인 값으로 변환)
	sprite->inv_det = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); // required for correct matrix multiplication

	//sprite->pos[X]/[Y]를 카메라 시점에서 관찰한 상대적 위치로 변환한 좌표 -> sprite->trans[X]/[Y]
	sprite->trans[X] = sprite->inv_det * (info->dirY * sprite->pos[X] - info->dirX * sprite->pos[Y]);
	sprite->trans[Y] = sprite->inv_det * (-info->planeY * sprite->pos[X] + info->planeX * sprite->pos[Y]); 
	// this is actually the depth inside the screen, 
	//that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

	sprite->screen_x = (int)((WIN_WIDTH / 2) * (1 + sprite->trans[X] / sprite->trans[Y]));
	// printf("sprite[%d].screen_x = %d ", idx, sprite->screen_x);

	// parameters for scaling and moving the sprites
	sprite->u_div = 1.5; //가로방향
	sprite->v_div = 1.5; //세로방향
	// #define vMove 200.0 // 64 ~ 200
	// -> sprite->v_move
	sprite->vm_screen = (int)(vars->sprite.v_move / sprite->trans[Y]);

	// calculate height of the sprite on screen
	sprite->sp_height = (int)fabs((WIN_HEIGHT / sprite->trans[Y]) / sprite->v_div); 
	// using "sprite->trans[Y]" instead of the real distance prevents fisheye
	// calculate lowest and highest pixel to fill in current stripe
	//스프라이트 요소는 화면에서 무조건 세로 중앙에 위치하기 때문에 + WIN_HEIGT / 2
	sprite->d_start_y = -sprite->sp_height / 2 + WIN_HEIGHT / 2 + sprite->vm_screen;
	if (sprite->d_start_y < 0)
		sprite->d_start_y = 0;
	sprite->d_end_y = sprite->sp_height / 2 + WIN_HEIGHT / 2 + sprite->vm_screen;
	if (sprite->d_end_y >= WIN_HEIGHT)
		sprite->d_end_y = WIN_HEIGHT - 1;

	// calculate width of the sprite
	sprite->sp_width = (int)fabs((WIN_HEIGHT / sprite->trans[Y]) / sprite->u_div);

	//스프라이트 요소가 모두 가로 중앙이 아니기 때문에 sp_width는 + sprite->screen_x로 함.
	sprite->d_start_x = -sprite->sp_width / 2 + sprite->screen_x;
	if (sprite->d_start_x < 0)
		sprite->d_start_x = 0;
	sprite->d_end_x = sprite->sp_width / 2 + sprite->screen_x;
	if (sprite->d_end_x >= WIN_WIDTH)
		sprite->d_end_x = WIN_WIDTH - 1;

	// loop through every vertical stripe of the sprite on screen
	sprite_to_screen(vars, sp[idx].texture, sprite->d_start_x);
}*/