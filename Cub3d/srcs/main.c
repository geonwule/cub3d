/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:57 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/25 21:37:40 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	map[15][34] = {
        "        1111111111111111111111111",
        "        10000000001100000000M0001",
        "        1011000001110000000000001",
        "        100100M00000000000M000001",
        "111111111011000001110000000000001",
        "100000000011000001110333131211111",
        "1111011111111101110000001M001    ",
        "11110111111111011201010000002    ",
        "11000000110101011200000000002    ",
        "100000M0000000001200000010003    ",
        "100000000000000011010100B0003    ",
        "1100000111010101111101111000211  ",
        "11110111 1110101 101111010002    ",
        "11111111 1111111 111111111111    "
    };

#ifdef DEBUG_LEAK
void	leaks(void)
{
	system("leaks cub3d");
}
#endif

void	print_error(char *str, t_vars *vars)
{
	printf("Error\n");
	printf("%s\n", str);
//	vars_free(vars);
	exit(1);
}

int main(int ac, char **av)
{
	#ifdef DEBUG_LEAK
	atexit(leaks); //tmp
	#endif
    t_vars  vars;

	if (ac != 2)
	{
		print_error("Need one arguement", &vars);
		return (RETURN_FAILURE);
	}
	vars_allocation(&vars);

	read_file(&vars, av[1]);


//    vars->mlx = mlx_init();
//    vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
//	vars_init(vars);
//	mlx_hook(vars->win, KEY_PRESS, PRESS_MASK, key_press, vars);
//	mlx_hook(vars->win, KEY_RELEASE, RELEASE_MASK, key_release, vars);
//	mlx_hook(vars->win, MOUSE_BUTTON, BUTTON_MASK, handle_mouse_button, vars);
//	mlx_hook(vars->win, MOUSE_MOVE, MOVE_MASK, handle_mouse_move, vars);
//	mlx_loop_hook(vars->mlx, rendering, vars);
//    mlx_hook(vars->win, WINDOW_DESTROY, DESTROY_MASK, exit_game, vars);
// 	mlx_loop(vars->mlx);

	return (RETURN_SUCCESS);
}
