#include "cub3d.h"

void	init_ray(t_info *info, t_ray *ray, int x)
{
    ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir[X] = info->dirX + info->planeX * ray->camera_x;
	ray->dir[Y] = info->dirY + info->planeY * ray->camera_x;
	ray->map[X] = (int)info->posX;
	ray->map[Y] = (int)info->posY;
	ray->delta_d[X] = fabs(1 / ray->dir[X]);
	ray->delta_d[Y] = fabs(1 / ray->dir[Y]);
	ray->hit = 0;
}

void	check_ray_dir(t_info *info, t_ray *ray)
{
    if (ray->dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_d[X] = (info->posX - ray->map[X]) * ray->delta_d[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_d[X] = (ray->map[X] + 1.0 - info->posX) * ray->delta_d[X];
	}
	if (ray->dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_d[Y] = (info->posY - ray->map[Y]) * ray->delta_d[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_d[Y] = (ray->map[Y] + 1.0 - info->posY) * ray->delta_d[Y];
	}
}

void	dda(t_vars *vars, char **map, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_d[X] < ray->side_d[Y])
		{
			ray->side_d[X] += ray->delta_d[X];
			ray->map[X] += ray->step[X];
			if (ray->step[X] < 0)
				ray->side = TEX_NO;
			else
				ray->side = TEX_SO;
		}
		else
		{
			ray->side_d[Y] += ray->delta_d[Y];
			ray->map[Y] += ray->step[Y];
			if (ray->step[Y] < 0)
				ray->side = TEX_EA;
			else
				ray->side = TEX_WE;
		}
		if (map[ray->map[X]][ray->map[Y]] == '1' || map[ray->map[X]][ray->map[Y]] == 'B')
			ray->hit = 1;
		if (map[ray->map[X]][ray->map[Y]] == 'M' && vars->data.monster_come == 0)
		{	
			vars->data.m_pos[X] = ray->map[X];
			vars->data.m_pos[Y] = ray->map[Y];
			vars->data.monster_come = 1;
		}
	}
}

void	check_ray_texture(t_info *info, t_ray *ray, char **map)
{
	if (ray->side <= 1) //north, south
		ray->perwalldist = (ray->map[X] - info->posX + (1 - ray->step[X]) / 2) / ray->dir[X];
	else //east, west
		ray->perwalldist = (ray->map[Y] - info->posY + (1 - ray->step[Y]) / 2) / ray->dir[Y];
	ray->line_height = (int)(WIN_HEIGHT / ray->perwalldist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;

	if (map[ray->map[X]][ray->map[Y]] == '1')
		ray->tex_num = ray->side; // ray->side is 0(north), 1(south), 2(east), 3(west)
	else if (map[ray->map[X]][ray->map[Y]] == 'B')
		ray->tex_num = TEX_DOOR;

	// calculate value of ray->wall_x
	if (ray->side <= 1) //north, south
		ray->wall_x = info->posY + ray->perwalldist * ray->dir[Y];
	else //east, west
		ray->wall_x = info->posX + ray->perwalldist * ray->dir[X];
	ray->wall_x -= floor(ray->wall_x);
}

void	apply_texture(t_info *info, t_ray *ray, int x, int y)
{
	// x coordinate on the texture
	ray->tex[X] = (int)(ray->wall_x * (double)TEX_WIDTH);
	if (ray->side <= 1 && ray->dir[X] > 0)
		ray->tex[X] = TEX_WIDTH - ray->tex[X] - 1;
	if (ray->side >= 2 && ray->dir[Y] < 0)
		ray->tex[X] = TEX_WIDTH - ray->tex[X] - 1;

	// how much to increase the texture coordinate perscreen pixel
	ray->t_step = 1.0 * TEX_HEIGHT / ray->line_height;

	// starting texture coordinate
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * ray->t_step;
	while (y < ray->draw_end)
	{
		// cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		ray->tex[Y] = (int)ray->tex_pos % (TEX_HEIGHT - 1); // & -> % AND연산자에서 %로
		ray->tex_pos += ray->t_step;
		ray->color = info->texture[ray->tex_num][TEX_HEIGHT * ray->tex[Y] + ray->tex[X]];
		info->buf[y][x] = ray->color;
		y++;
	}
}