/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:19:21 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/24 20:50:56 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../Libft/libft.h"
#include "../mlx_opengl/mlx.h" // mlx.h
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

# define NORTH "./texture/jeong/no.xpm"
# define SOUTH "./texture/jeong/so.xpm"
# define EAST "./texture/jeong/ea.xpm"
# define WEST "./texture/jeong/we.xpm"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define TEX_WIDTH 400	
# define TEX_HEIGHT 400

# define MAP_HEIGHT 15
# define MAP_WIDTH 34

// # define IMG_WIDTH 4000
// # define IMG_HEIGHT 3000

enum	e_pos
{
	X = 0,
	Y = 1,
	POS_X = 11,
	POS_Y = 26,
}	;

enum	e_return_value
{
	RETURN_SUCCESS = 0,
	RETURN_FAILURE,
}	;

enum	e_texture
{
	TEX_NUM = 8,
	TEX_NO = 0,
	TEX_SO,
	TEX_EA,
	TEX_WE,
	TEX_DOOR,
	TEX_MONSTER,
	TEX_POTION,
	TEX_NPC,
};

enum	e_key
{
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	B = 11,
	R = 15,
	Q = 12,
	E = 14,
	P = 35,
	ESC = 53,
	DEAD = 3,
	LEFT = 124,
	RIGHT = 123,
	SPACE = 49,
}	;

enum	e_hook_event
{
	KEY_PRESS = 2,
	PRESS_MASK = 1L<<0,

	KEY_RELEASE = 3,
	RELEASE_MASK = 1L<<1,

	MOUSE_BUTTON = 4,
	BUTTON_MASK = 1L<<2,
	
	MOUSE_MOVE = 6,
	MOVE_MASK = 1L<<6,

	WINDOW_DESTROY = 17,
	DESTROY_MASK = 0,
}	;

// typedef struct s_img
// {
// 	void	*ptr;
// 	char	*path;
// 	char	*data;
// 	int		w;
// 	int		h;
// 	int		bpp;
// 	int		lsize;
// 	int		end;
// }	t_img;

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

typedef struct s_dda
{
	double	ray_dir[2];
	int		map[2];
	double	side_dst[2];
	double	delta_dst[2];
	int		step[2];
	double	w_dst;
	int		side;
	int		l_height;
	int		draw[2];
	t_img	img;
	int		tex[2];
}	t_dda;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_ray;


typedef struct  s_info
{
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
}   t_info;

// typedef	struct s_map
// {
// 	char			*line;
// 	int				line_len;
// 	struct s_map	*prev;
// 	struct s_map	*next;
// }	t_map;

typedef	struct s_map
{
	int		height;
	int		width;
	char	*tmp_arr;
	char	**arr;
}	t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}	t_sprite;

typedef struct s_vars
{

	int		keyboard[1000];

    void	*mlx;
    void	*win;

	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	int		f[3];
	char	*ceiling;
	int		c[3];

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

    void    *img_ptr;
    char    *data;

    int     size_l;
    int     bpp;
    int     endian;
	
	t_map	*map;
	// ray
	t_ray	ray;
	t_info	*info;

	int				monster_come;
	int				m_speed;
	unsigned int	m_pos[2];
	unsigned int	m_num;
	
	void			*w_messege;
	unsigned int	warning_time;

	void			*potion;

	int				sprite_num; //sprite_num
	t_sprite		*sprite;
	int				v_move;
	int				v_i;

	//aim,shot
	void	*aim;
	void	*gun;

	int		hp;
	int		hp_before;

	void	*hp1;
	void	*hp2;
	void	*hp3;

	void	*damage;

	int		dead_check;
	void	*dead;

	int		hunt;
	void	*exp1;
	void	*exp2;

	int		level;
	void	*lv;

	int		gun_change;

	double	init_pos[2];
	double	init_dir[2];
	double	init_plane[2];
}   t_vars;

//vars_init
t_vars  *vars_allocation(t_vars *vars);
int		vars_init(t_vars *vars);
void	set_dir(t_info *info, double x, double y);
void	set_plane(t_info *info, double x, double y);

//background_init
void	fill_background(t_vars *vars, int ceiling[3], int floor[3]);

//map_read
int		map_read(char *map_path, t_vars *vars);

//map_error
int 	map_error(t_vars *vars);

//key_event
void	attack(t_vars *vars);
int		can_move(t_vars *vars, int y, int x);
int		key_release(int keycode, t_vars *vars);
int		key_press(int keycode, t_vars *vars);
void	monster_kill(t_vars *vars);
void	reset_game(t_vars *vars);

//mouse_event
int		handle_mouse_button(int button, int x, int y, void *args);
int		handle_mouse_move(int x, int y, void *args);

//redering
int		rendering(t_vars *vars);

//map_set
void	map_set(t_vars *vars);

//get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strdup_gnl(const char *s1, char *back);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

//mlx_function
void    *ft_xpm_file_to_image(void *mlx_ptr, char *path, int *w, int *h);
char    *ft_get_data_addr(void *img_ptr, int *bits, int *size, int *end);

//function
void    *ft_malloc(size_t size);
int		ft_open(char *file_path);
void	vars_free(t_vars *vars);
int		exit_game(t_vars *vars);
int		random_generator(int frequency);

//ft_lstcub
t_map	*ft_lstnew_cub(void *content);
t_map	*ft_lstlast_cub(t_map *lst);
void	ft_lstadd_back_cub(t_map **lst, t_map *new);
int		ft_lstsize_cub(t_map *lst);
#endif