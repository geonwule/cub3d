#include "cub3d.h"

void	attack(t_vars *vars)
{
	int		x;
	int		y;
	void	*shot;
	void	*shot2;

	vars->data.hand_change = 1;
	shot = ft_xpm_file_to_image(vars->mlx, "texture/etc/clo_1.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, shot, WIN_WIDTH / 12 * 5, WIN_HEIGHT / 3);
	shot2 = ft_xpm_file_to_image(vars->mlx, "texture/etc/clo_2.xpm", &x, &y);
	mlx_put_image_to_window(vars->mlx, vars->win, shot2, WIN_WIDTH / 12 * 5, WIN_HEIGHT / 3);
	monster_kill(vars, vars->info, vars->map.arr);
}

void	reset_game(t_vars *vars)
{
	char	**map = vars->map.arr;

	vars_free(vars);
	vars_allocation(vars);
	vars_init(vars);	
	for (int i = 0; i < vars->map.height; i++)
	{
		for (int j = 0; j < vars->map.width; j++)
		{
			if (map[i][j] == 'b')
				map[i][j] = 'B';
			else if (map[i][j] == 'M' || map[i][j] == 'P')
				map[i][j] = '0';
		}
	}
}