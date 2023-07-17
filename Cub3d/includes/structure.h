/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:21:00 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/16 14:57:52 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "define.h"

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_ray
{
	double	camera_x;
	double	dir[2];
	int		map[2];
	double	side_d[2];
	double	delta_d[2];
	int		step[2];
	int		hit;
	double	perwalldist;
	int		side;

	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex[2];
	double	t_step;
	double	tex_pos;
	int		color;
}	t_ray;

typedef struct s_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	void	*mlx;
	void	*win;
	double	move_speed;
	double	rot_speed;
	t_img	img;
	int		buf[WIN_HEIGHT][WIN_WIDTH];
	double	z_buffer[WIN_WIDTH];
	int		**texture;
	int		draw_start;
	int		draw_end;
}			t_info;

typedef struct s_sp
{
	double		x;
	double		y;
	int			texture;
}	t_sp;

typedef struct s_sprite
{
	t_sp	*sp;
	int		sprite_num;
	int		v_move;
	int		v_i;
	double	pos[2];
	double	inv_det;
	double	trans[2];
	int		screen_x;
	double	u_div;
	double	v_div;
	int		vm_screen;
	int		sp_height;
	int		sp_width;
	int		d_start_x;
	int		d_start_y;
	int		d_end_x;
	int		d_end_y;
}	t_sprite;

typedef struct s_map_info
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	int		f[3];
	char	*ceiling;
	int		c[3];
}			t_map_info;

typedef struct s_map
{
	t_map_info	info;
	int			height;
	int			width;
	char		**arr;
}	t_map;

typedef struct s_mini
{
	void	*north_x;
	void	*south_x;
	void	*west_x;
	void	*east_x;

	void	*player_x;	
	void	*empty_x;
	void	*wall_x;
	void	*door_x;
	void	*monster_x;
	void	*potion_x;
	void	*dir_x;
	void	*npc_x;
}	t_mini;

typedef struct s_xpm
{
	void	*quest_start;
	void	*quest_ing;
	void	*quest_end;
	void	*dead;
	void	*damage;
	void	*aim;
	void	*w_messege;
	void	*hand1;
	void	*hand2;
	void	*hp1;
	void	*hp2;
	void	*hp3;
	void	*exp1;
	void	*exp2;
	void	*lv;
}	t_xpm;

typedef struct s_data
{
	int				keyboard[1000];
	int				hp;
	int				hp_before;
	int				dead_check;
	int				hunt;
	int				level;
	int				hand_change;
	int				monster_come;
	int				m_speed;
	unsigned int	m_pos[2];
	unsigned int	m_num;
	unsigned int	warning_time;
	int				npc_talk;
	int				quest_num;
	int				quest_monster_num;
	int				mouse_x;
	int				mouse_old_x;
	int				mouse_y;
	int				mouse_old_y;
	double			init_pos[2];
	double			init_dir[2];
	double			init_plane[2];
	unsigned int	render_i;
}	t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_mini		mini;
	t_xpm		xpm;
	t_info		info;
	t_data		data;
	t_sprite	sprite;
}	t_vars;

#endif