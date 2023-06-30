#include "cub3d.h"

int	can_move(t_vars *vars, int x, int y)
{
	char	spot;

	spot = vars->map.arr[x][y];
	if (spot == 'P')
	{
		vars->map.arr[x][y] = '0';
		if (vars->hp < 3)
			vars->hp++;
		return (1);
	}
	else if (spot == '0' || spot == 'N' || spot == 'S' \
		|| spot == 'W' || spot == 'E' || spot == 'b')
		return (1);
	return (0);
}

static void	key_check(t_vars *vars)
{
	t_info	*info = vars->info;
	
	if (vars->keyboard[ESC])
       	exit_game(vars);
	if (vars->keyboard[W])
	{
		if (can_move(vars, (int)(info->posX + info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX += info->dirX * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY + info->dirY * info->moveSpeed)))
			info->posY += info->dirY * info->moveSpeed;
	}
	if (vars->keyboard[S])
	{
		if (can_move(vars, (int)(info->posX - info->dirX * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX -= info->dirX * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY - info->dirY * info->moveSpeed)))
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (vars->keyboard[D])
	{
		if (can_move(vars, (int)(info->posX + info->dirY * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX += info->dirY * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY - info->dirX * info->moveSpeed)))
			info->posY -= info->dirX * info->moveSpeed;
	}
	if (vars->keyboard[A])
	{
		if (can_move(vars, (int)(info->posX - info->dirY * info->moveSpeed) \
			, (int)(info->posY)))
			info->posX -= info->dirY * info->moveSpeed;
		if (can_move(vars, (int)(info->posX) \
			, (int)(info->posY + info->dirX * info->moveSpeed)))
			info->posY += info->dirX * info->moveSpeed;
	}
	if (vars->keyboard[LEFT])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (vars->keyboard[RIGHT])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
}

static void	mouse_check(t_vars *vars)
{
	t_info	*info = vars->info;

	if (vars->mouse_x > vars->mouse_old_x) // right
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	if (vars->mouse_x < vars->mouse_old_x) // left
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (++vars->render_i % 5 == 0)
	{
		vars->mouse_old_x = vars->mouse_x;
		vars->mouse_old_y = vars->mouse_y;
	}
}

void	check_key_and_mouse(t_vars *vars)
{
    key_check(vars);
	mouse_check(vars);
}