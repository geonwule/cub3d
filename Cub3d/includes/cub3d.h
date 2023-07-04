/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:19:21 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/04 19:46:02 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../Libft/libft.h"
#include "../mlx_opengl/mlx.h" // mlx.h
#include "define.h"
#include <fcntl.h> // open
#include <unistd.h> //close, read, write
#include <stdio.h> // printf, perror, strerror
#include <stdlib.h> // malloc, free, exit
#include <math.h> // math.h

//debug
// #define MAP_DEBUG
// # define DEBUG
// # define KEY_DEBUG
// # define DEBUG_LEAK
// #define DEBUG_MON

typedef	struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

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

typedef struct  s_info
{
	//jonn
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;

    double  planeX;
    double  planeY;
    void    *mlx;
	void	*win;
	double	moveSpeed;
	double	rotSpeed;

	t_img	img;
	int		buf[WIN_HEIGHT][WIN_WIDTH];
	double	zBuffer[WIN_WIDTH];
	int		**texture;
}	t_info;

typedef struct	s_sp
{
	double		x;
	double		y;
	int			texture;
}	t_sp;

typedef struct	s_sprite
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

typedef	struct s_map
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

//vars_init
void	init_vars(t_vars *vars);
int		init_vars_info(t_vars *vars);

//background_init
void	fill_background(t_vars *vars, int ceiling[3], int floor[3]);

// evnet/check_key_and_mouse.c
int		can_move(t_vars *vars, int x, int y);
void	check_key_and_mouse(t_vars *vars);

// evnet/check_key_and_mouse2.c
void	move_forward_backward(t_vars *vars, t_info *info, double move_speed);
void	move_left_right(t_vars *vars, t_info *info, double move_speed);
void	rotate_left_right(t_info *info, double rot_speed);
void	rotate_left(t_info *info, double rot_speed);
void	rotate_right(t_info *info, double rot_speed);

//event/event_function1.c
void	attack(t_vars *vars);
void	reset_game(t_vars *vars);

//event/event_function2.c
void	return_ellinia(t_vars *vars);
void	open_door_tell_npc(t_vars *vars, char **map);
void	adjust_gamespeed(t_info *info, int keycode);
void	turn_back(t_info *info);

//evnet/key_event
int		key_release(int keycode, t_vars *vars);
int		key_press(int keycode, t_vars *vars);

//event/manage_monster
void	manage_monster(t_vars *vars);

//evnet/monster_kill
void	monster_kill(t_vars *vars, t_info *info, char **map);

//evnet/mouse_event
int		handle_mouse_button(int button, int x, int y, void *args);
int		handle_mouse_move(int x, int y, void *args);

//evnet/print_window
void	print_window1(t_vars *vars);
void	print_window2(t_vars *vars);

//evnet/ray_casting
void	ray_casting(t_vars *vars, t_info *info, char **map);

//event/ray_function
void	init_ray(t_info *info, t_ray *ray, int x);
void	check_ray_dir(t_info *info, t_ray *ray);
void	check_ray_texture(t_info *info, t_ray *ray, char **map);
void	apply_texture(t_info *info, t_ray *ray, int x, int y);

// event/ray_function_dda.c
void	dda(t_vars *vars, char **map, t_ray *ray);

//evnet/sprite
void	sprite(t_vars *vars);

//event/sprite2
int		*sort_sprite(t_vars *vars, t_info *info, t_sp *sprite);
void	calculate_sprite(t_vars *vars, t_info *info, int idx, t_sprite *sprite);

//event/redering
int		rendering(t_vars *vars);

// event/mini_map.c
void	mini_map(t_vars *vars);

//get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strdup_gnl(const char *s1, char *back);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

//mlx_function
void	*ft_xpm_file_to_image(void *mlx_ptr, char *path, int *w, int *h);
char	*ft_get_data_addr(void *img_ptr, int *bits, int *size, int *end);

//function
void	*ft_malloc(size_t size);
int		ft_open(char *file_path);
void	free_vars(t_vars *vars);
int		exit_game(t_vars *vars);
int		random_generator(int frequency);

//ft_lstcub
t_map	*ft_lstnew_cub(void *content);
t_map	*ft_lstlast_cub(t_map *lst);
void	ft_lstadd_back_cub(t_map **lst, t_map *new);
int		ft_lstsize_cub(t_map *lst);

// test/print.c
void	print_texture(t_vars *vars);
void	print_color(t_vars *vars);
void	print_arr_2d(char **arr);
void	print_lst(t_list *head);

//	utils/print_error.c
void	print_error(char *str, t_vars *vars);

// utils/free.c
void	free_arr_2d(char ***arr);
void	free_map(t_map *map);
void	free_lst(t_list **head);

// utils/alloc_copy_str.c
char	*allocate_and_copy_string(char *src, t_vars *vars);

// utils/size_arr_2d.c
int		size_arr_2d(char **arr);

// parsing/check.c
void	check_file(t_vars *vars, char *path);
int		check_texture(char *line);
int		check_color(char *line);

// parsing/read_file.c
void	read_file(t_vars *vars, char *path);

// parsing/set.c
int		set_texture(char **arr, t_vars *vars);
void	set_map(t_vars *vars, int fd, char *line);

// parsing/set_color.c
int		set_color(char **arr, t_vars *vars);

// parsing/check_map.c
int		check_map(t_vars *vars);

// parsing/check_map2.c
void	init_dir_plane_ns(t_vars *vars, char type);
void	init_dir_plane_ew(t_vars *vars, char type);

// parsing/set_color_utils.c
int		ft_atoi_color(const char *str);

#endif
