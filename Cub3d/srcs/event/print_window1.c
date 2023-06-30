#include "cub3d.h"

static void game_key_explain(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 3 \
		, 0xFFFFFF, "Key setting");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 5 \
		, 0xFFFFFF, "W/A/S/D : character move");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 7 \
		, 0xFFFFFF, "Q : turn back");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 9 \
		, 0xFFFFFF, "<-/->/mouse_move : Direct move");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 11 \
		, 0xFFFFFF, "Space/mouse_left : Attack");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 13 \
		, 0xFFFFFF, "R : return respone");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 15 \
		, 0xFFFFFF, "N/M : Game speed slow/fast");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 17 \
		, 0xFFFFFF, "P : game reset");
	mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 10 * 8, WIN_HEIGHT / 100 * 19 \
		, 0xFFFFFF, "B : Door open/close, NPC contect");
}

static void press_b(t_vars *vars)
{
	t_info	*info = vars->info;
	char	**map = vars->map.arr;

	double		x, y;
	const int	dx[4] = {-1, 1, 0, 0};
	const int	dy[4] = {0, 0, -1, 1};
	char		spot;

	for (int i = 0; i < 4; i++)
	{
		x = info->posX + dx[i];
		y = info->posY + dy[i]; 
		spot = map[(int)x][(int)y];
		if (x < 0 || x >= WIN_HEIGHT \
			|| y < 0 || y >= WIN_WIDTH)
			continue ;
		if (spot == 'B' || spot == 'b' || spot == 'H')
		{
			mlx_string_put(vars->mlx, vars->win, WIN_WIDTH / 100 * 47, WIN_HEIGHT / 100 * 70 \
				, 0xFFFFFF, "press key 'B'");
			return ;
		}
	}	
}

static void	aim_point(t_vars *vars)
{
	if (vars->data.hand_change)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.hand2, WIN_WIDTH / 10 * 3, WIN_HEIGHT / 9 * 6);
		vars->data.hand_change = 0;
	}
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.hand1, WIN_WIDTH / 9 * 1, WIN_HEIGHT / 9 * 5);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.aim, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

static void	hp_exp(t_vars *vars)
{
	if (vars->data.hp == 3)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.hp3, WIN_WIDTH * 0, WIN_HEIGHT / 100 * 98);
	else if (vars->data.hp == 2)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.hp2, WIN_WIDTH * 0, WIN_HEIGHT / 100 * 98);
	else if (vars->data.hp == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.hp1, WIN_WIDTH * 0, WIN_HEIGHT / 100 * 98);
	else if (vars->data.hp == 0)
	{
		vars->data.dead_check = 1;
		return ;
	}
	if (vars->data.hunt % 2 == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.exp1, WIN_WIDTH / 100 * 34, WIN_HEIGHT / 100 * 98);
	else if (vars->data.hunt % 2 == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->xpm.exp2, WIN_WIDTH / 100 * 34, WIN_HEIGHT / 100 * 98);
}

void    print_window1(t_vars *vars)
{
    game_key_explain(vars);
	press_b(vars);
	aim_point(vars);
	hp_exp(vars);
}
