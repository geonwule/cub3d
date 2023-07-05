/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:19:21 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/05 14:23:41 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../Libft/libft.h"
# include "../mlx_opengl/mlx.h"
# include "define.h"
# include "structure.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>

// init/init_vars_info.c
int		init_vars_info(t_vars *vars);

// init/init_vars.c
void	init_vars(t_vars *vars);

// init/load_texture.c
void	load_texture(t_vars *vars, t_info *info);

// init/img_xpm_set.c
void	img_xpm_set(t_vars *vars);

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

// event/event_function1.c
void	attack(t_vars *vars);
void	reset_game(t_vars *vars);

// event/event_function2.c
void	return_ellinia(t_vars *vars);
void	open_door_tell_npc(t_vars *vars, char **map);
void	adjust_gamespeed(t_info *info, int keycode);
void	turn_back(t_info *info);

// evnet/key_event
int		key_release(int keycode, t_vars *vars);
int		key_press(int keycode, t_vars *vars);

// event/manage_monster
void	manage_monster(t_vars *vars);

// evnet/monster_kill
void	monster_kill(t_vars *vars, t_info *info, char **map);

// evnet/mouse_event
int		handle_mouse_button(int button, int x, int y, void *args);
int		handle_mouse_move(int x, int y, void *args);

// evnet/print_window
void	print_window1(t_vars *vars);
void	print_window2(t_vars *vars);

// evnet/ray_casting
void	ray_casting(t_vars *vars, t_info *info, char **map);

// event/ray_function
void	init_ray(t_info *info, t_ray *ray, int x);
void	check_ray_dir(t_info *info, t_ray *ray);
void	check_ray_texture(t_info *info, t_ray *ray, char **map);
void	apply_texture(t_info *info, t_ray *ray, int x, int y);

// event/ray_function_dda.c
void	dda(t_vars *vars, char **map, t_ray *ray);

// evnet/sprite
void	sprite(t_vars *vars);

// event/sprite2
int		*sort_sprite(t_vars *vars, t_info *info, t_sp *sprite);
void	calculate_sprite(t_vars *vars, t_info *info, int idx, t_sprite *sprite);

// event/redering
int		rendering(t_vars *vars);

// event/mini_map.c
void	mini_map(t_vars *vars);

// get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strdup_gnl(const char *s1, char *back);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin_gnl(char const *s1, char const *s2);

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

// utils/print_error.c
void	print_error(char *str, t_vars *vars);

// utils/free.c
void	free_arr_2d(char ***arr);
void	free_map(t_map *map);
void	free_lst(t_list **head);

// utils/alloc_copy_str.c
char	*allocate_and_copy_string(char *src, t_vars *vars);

// utils/size_arr_2d.c
int		size_arr_2d(char **arr);

// utils/random_generator
int		random_generator(int frequency);

// utils/ft_malloc.c
void	*ft_malloc(size_t size);

// utils/free_vars.c
void	free_vars(t_vars *vars);

// utils/exit_game.c
int		exit_game(t_vars *vars);

// utils/ft_get_data_addr.c
char	*ft_get_data_addr(void *img_ptr, int *bits, int *size, int *end);

// utils/ft_xpm_file_to_image.c
void	*ft_xpm_file_to_image(void *mlx_ptr, char *path, int *w, int *h);

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
