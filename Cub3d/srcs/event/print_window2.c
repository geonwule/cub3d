#include "cub3d.h"

static void	level_up(t_vars *vars)
{
	char	*level_str;
	if (vars->hunt != 0 && vars->hunt % 2 == 0)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->lv, WIN_WIDTH / 9 * 2, WIN_HEIGHT / 5 * 2);
		vars->level += 1;
		vars->hunt = 0;
	}
	level_str = ft_itoa(vars->level); //overflow protect need!
	mlx_string_put(vars->mlx, vars->win, 50, 710, 0xFFFFFF, level_str);
	
	free(level_str);
}

static void	warning_message(t_vars *vars)
{
	if (vars->m_num)
		return ;
	vars->warning_time++;
	if (vars->warning_time % 7 == 0) //깜빡이게
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->w_messege \
		, WIN_WIDTH / 100 * 20, WIN_HEIGHT / 100 * 35);
}

static void	npc_quest(t_vars *vars)
{
	if (vars->quest_num != 0)
		quest_progress(vars);
	if (vars->npc_talk == 0)
		return ;
	if (vars->quest_num == 0) // init
		mlx_put_image_to_window(vars->mlx, vars->win, vars->quest_start \
		, WIN_WIDTH / 100 * 35, WIN_HEIGHT / 100 * 30);
	else if (vars->quest_num == 1)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->quest_ing \
		, WIN_WIDTH / 100 * 35, WIN_HEIGHT / 100 * 30);
	else if (vars->quest_num == 2)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->quest_end \
		, WIN_WIDTH / 100 * 35, WIN_HEIGHT / 100 * 30);
}

static void	damaged_or_recovery(t_vars *vars)
{
	if (vars->hp_before > vars->hp)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->damage, WIN_WIDTH / 100 * 12, 0);
	vars->hp_before = vars->hp;
}

void    print_window2(t_vars *vars)
{
    level_up(vars);
	warning_message(vars);
	npc_quest(vars);
	damaged_or_recovery(vars);
}