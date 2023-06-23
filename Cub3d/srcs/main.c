/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:57 by geonwule          #+#    #+#             */
/*   Updated: 2023/06/23 12:50:41 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	map[15][34] = {
        "        1111111111111111111111111",
        "        1000000000110000000000001",
        "        1011000001110000000000001",
        "        1001000000000000000000001",
        "111111111011000001110000000000001",
        "100000000011000001110BBB13B211111",
        "1111011111111101110000001M001    ",
        "111101111111110BB201010000002    ",
        "11000000110101000000000000002    ",
        "1M0000000M0000001200000010003    ",
        "10M0M00M0000000011010100B0003    ",
        "1100000111010101111101111000211  ",
        "11110111 1110101 111111110002    ",
        "11111111 1111111 111111111111    "
    };

#ifdef DEBUG_LEAK
void	leaks(void)
{
	system("leaks cub3d");
}
#endif

int main(int ac, char **av)
{
	#ifdef DEBUG_LEAK
	atexit(leaks); //tmp
	#endif
    t_vars  vars;

    // if (ac != 2)
    // {
    //     printf("arg_error\n");
    //     return (RETURN_FAILURE);
    // }
    vars_allocation(&vars);
    if (map_read(av[1], &vars) || map_error(&vars))
	{
		vars_free(&vars);
		return (RETURN_FAILURE);
	}
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	vars_init(&vars);
	mlx_hook(vars.win, KEY_PRESS, PRESS_MASK, key_press, &vars);
	mlx_hook(vars.win, KEY_RELEASE, RELEASE_MASK, key_release, &vars);
	mlx_hook(vars.win, MOUSE_BUTTON, BUTTON_MASK, handle_mouse_button, &vars);
	mlx_hook(vars.win, MOUSE_MOVE, MOVE_MASK, handle_mouse_move, &vars);
	mlx_loop_hook(vars.mlx, rendering, &vars);
    mlx_hook(vars.win, WINDOW_DESTROY, DESTROY_MASK, exit_game, &vars);
 	mlx_loop(vars.mlx);
	return (RETURN_SUCCESS);
}
