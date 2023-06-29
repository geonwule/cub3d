#include "cub3d.h"

static void	monster_rezen(t_vars *vars)
{
	int		i;
	int		j;
	char	**map;

    map = vars->map.arr;
	if (vars->m_num)
		return ;
	if (vars->warning_time < 50) //warning_time
		return ;
	vars->warning_time = 0;
	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (i > vars->map.height * 0.7 && vars->map.width * 0.5) // respone area
				break ;
			if (map[i][j] == '0' && random_generator(2) \
				&& i != (int)vars->info->posX && j != (int)vars->info->posY)
			{
				map[i][j] = 'M';
				vars->m_num++;
				usleep(1);
			}
			j++;
		}
		i++;
	}
}

static void monster_move(t_vars *vars, int x_or_y, int step)
{
	char	**map;
	int		x;
	int		y;

	x = vars->m_pos[X];
	y = vars->m_pos[Y];
	map = vars->map.arr;
	map[x][y] = '0';
	if (x_or_y == X)
	{
		map[x + step][y] = 'M';
		vars->m_pos[X] += step;
	}
	else
	{
		map[x][y + step] = 'M';
		vars->m_pos[Y] += step;
	}
}

static void	move_x(t_vars *vars, t_info *info, char **map)
{
	int	x;
	int	y;

	x = vars->m_pos[X];
	y = vars->m_pos[Y];
	if ((int)info->posX < x && map[x - 1][y] == '0')
	{
		if (((int)info->posX == x - 1 && (int)info->posY == y) && vars->hp > 0)
			vars->hp -= 1;
		else
			monster_move(vars, X, -1);
	}
	else if ((int)info->posX > x && map[x + 1][y] == '0')
	{
		if (((int)info->posX == x + 1 && (int)info->posY == y))
			vars->hp -= 1;
		else
			monster_move(vars, X, 1);
	}
}

static void	move_y(t_vars *vars, t_info *info, char **map)
{
	int	x;
	int	y;

	x = vars->m_pos[X];
	y = vars->m_pos[Y];
	if ((int)info->posY < y && map[x][y - 1] == '0')
	{
		if ((int)info->posX == x && (int)info->posY == y - 1)
			vars->hp -= 1;
		else
			monster_move(vars, Y, -1);
	}
	else if ((int)info->posY > y && map[x][y + 1] == '0')
	{
		if ((int)info->posX == x && (int)info->posY == y + 1)
			vars->hp -= 1;
		else
			monster_move(vars, Y, 1);
	}
}

static void	monster_come_on(t_vars *vars)
{
	t_info	*info = vars->info;
	char	**map = vars->map.arr;

	if (!vars->monster_come || ++vars->m_speed % 30 != 0 \
		|| map[vars->m_pos[X]][vars->m_pos[Y]] != 'M' \
		|| vars->npc_talk)
		return ;
	move_x(vars, info, map);
	move_y(vars, info, map);
}

void    manage_monster(t_vars *vars)
{
    monster_rezen(vars);
    monster_come_on(vars);
}