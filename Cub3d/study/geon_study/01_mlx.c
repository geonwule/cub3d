#include "01_mlx.h"

int world_map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int key_press(int keycode, t_vars *vars)
{
    if (keycode == K_ESC)
        exit(0);
    if (keycode == K_W)
    {
        if (world_map[(int)(vars->pos[X] + vars->dir[X] * vars->moveSpeed)][(int)vars->pos[Y]] == 0)
            vars->pos[X] += vars->dir[X] * vars->moveSpeed;
        if (world_map[(int)vars->pos[X]][(int)(vars->pos[Y] + vars->dir[Y] * vars->moveSpeed)] == 0)
            vars->pos[Y] += vars->dir[Y] * vars->moveSpeed;
    }
    if (keycode == K_S)
    {
        if (world_map[(int)(vars->pos[X] - vars->dir[X] * vars->moveSpeed)][(int)vars->pos[Y]] == 0)
            vars->pos[X] -= vars->dir[X] * vars->moveSpeed;
        if (world_map[(int)(vars->pos[X])][(int)(vars->pos[Y] - vars->dir[Y] * vars->moveSpeed)] == 0)
            vars->pos[Y] -= vars->dir[Y] * vars->moveSpeed;
    }
    if (keycode == K_A)
    {
        double  oldDirX = vars->dir[X];
        vars->dir[X] = vars->dir[X] * cos(vars->rotSpeed) - vars->dir[Y] * sin(vars->rotSpeed);
        vars->dir[Y] = oldDirX * sin(vars->rotSpeed) + vars->dir[Y] * cos(vars->rotSpeed);
        double oldPlaneX = vars->plane[X];
        vars->plane[X] = vars->plane[X] * cos(vars->rotSpeed) - vars->plane[Y] * sin(vars->rotSpeed);
        vars->plane[Y] = oldPlaneX * sin(vars->rotSpeed) + vars->plane[Y] * cos(vars->rotSpeed);
    }
    if (keycode == K_D)
    {
        double  oldDirX = vars->dir[X];
        vars->dir[X] = vars->dir[X] * cos(-vars->rotSpeed) - vars->dir[Y] * sin(-vars->rotSpeed);
        vars->dir[Y] = oldDirX * sin(-vars->rotSpeed) + vars->dir[Y] * cos(-vars->rotSpeed);
        double  oldPlaneX = vars->plane[X];
        vars->plane[X] = vars->plane[X] * cos(-vars->rotSpeed) - vars->plane[Y] * sin(-vars->rotSpeed);
        vars->plane[Y] = oldPlaneX * sin(-vars->rotSpeed) + vars->plane[Y] * cos(-vars->rotSpeed);
    }
    return (0);
}

void    fill_background(t_vars *vars)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT / 2)
                mlx_pixel_put(vars->mlx, vars->win, x, y, 0x00FF00);
            else
                mlx_pixel_put(vars->mlx, vars->win, x, y, 0x000080);
        }
    }
}

void    verLine(t_vars *vars, int x, int drawStart, int drawEnd, int color)
{
    for (int y = drawStart; y <= drawEnd; y++)
    {
        mlx_pixel_put(vars->mlx, vars->win, x, y, color);
    }
}

void    ray_casting(t_vars *vars)
{
    double  pos[2];
    pos[X] = vars->pos[X];
    pos[Y] = vars->pos[Y];

    double dir[2];
    dir[X] = vars->dir[X];
    dir[Y] = vars->dir[Y];

    double plane[2];
    plane[X] = vars->plane[X];
    plane[Y] = vars->plane[Y];

    for (int x = 0; x < WIDTH; x++)
    {
        double  cameraX = 2 * x / (double)(WIDTH) - 1;
        double  rayDirX = dir[X] + plane[X] * cameraX;
        double  rayDirY = dir[Y] + plane[Y] * cameraX;

        int map[2];
        map[X] = (int)pos[X];
        map[Y] = (int)pos[Y];

        double  sideDist[2];

        double  deltaDist[2];

        deltaDist[X] = fabs(1 / rayDirX);
        deltaDist[Y] = fabs(1 / rayDirY);
        double  perWallDist;

        int step[2];

        int hit = 0;
        int side; //was a NS or EW wall hit?

        if (rayDirX < 0)
        {
            step[X] = -1;
            sideDist[X] = (pos[X] - map[X]) * deltaDist[X];
        }
        else
        {
            step[X] = 1;
            sideDist[X] = (map[X] + 1 - pos[X]) * deltaDist[X];
        }
        if (rayDirY < 0)
        {
            step[Y] = -1;
            sideDist[Y] = (pos[Y] - map[Y]) * deltaDist[Y];
        }
        else
        {
            step[Y] = 1;
            sideDist[Y] = (map[Y] + 1 - pos[Y]) * deltaDist[Y];
        }

        while (hit == 0)
        {
            if (sideDist[X] < sideDist[Y])
            {
                sideDist[X] += deltaDist[X];
                map[X] += step[X];
                side = 0;
            }
            else
            {
                sideDist[Y] += deltaDist[Y];
                map[Y] += step[Y];
                side = 1;
            }
            if (world_map[map[Y]][map[X]] > 0)
                hit = 1;
        }

        if (side == 0) // X_hit
        {
            perWallDist = (map[X] - pos[X] + (1 - step[X]) / 2) / rayDirX;
        }
        else // Y_hit
        {
            perWallDist = (map[Y] - pos[Y] + (1 - step[Y]) / 2) / rayDirY;
        }

        int lineheight = (int)(HEIGHT / perWallDist);

        int drawStart = -lineheight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineheight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        int color;
        if (world_map[map[Y]][map[X]] == 1)
            color = 0xFF0000;
        else
            color = 0xFFFF00;

        if (side == 1)
            color /= 2;
        verLine(vars, x, drawStart, drawEnd, color);
    }
}

void    (t_vars *vars)
{
    void    *mini = mlx_new_image(vars->mlx, WIDTH / 4, HEIGHT / 4);

    int bit, size, endian;
    int *addr = (int *)mlx_get_data_addr(mini, &bit, &size, &endian);
    for (int y = 0; y < HEIGHT / 4; y++)
    {
        for (int x = 0; x < WIDTH / 4; x++)
        {
            int color;
            int map_x = (double)x / (WIDTH / 4) * 10;
            int map_y = (double)y / (HEIGHT / 4) * 10;
            if (map_y == (int)vars->pos[Y] && map_x == (int)vars->pos[X])
                color = 0x00FF00;
            else if (world_map[map_y][map_x] == 1)
                color = 0x0000FF;
            else
                color = 0xFF0000;
            addr[y * (WIDTH / 4) + x] = color;
        }
    }
    mlx_put_image_to_window(vars->mlx, vars->win, mini, 0, 0);
}

int i = 0;
int rendering(t_vars *vars)
{
    // printf("%lf %lf %lf %lf %lf %lf\n", vars->pos[X], vars->pos[Y], vars->dir[X], vars->dir[Y], vars->plane[X], vars->plane[Y]);
    // exit(0);
    mlx_clear_window(vars->mlx, vars->win);
    fill_background(vars);
    ray_casting(vars);
    mini_map(vars);

    printf("%d\n", ++i);
    return (0);
}

int main()
{
    t_vars  vars;

    //pos
    vars.pos[X] = 2;
    vars.pos[Y] = 3;

    //dir
    vars.dir[X] = 1;
    vars.dir[Y] = 0;

    //plane
    vars.plane[X] = 0;
    vars.plane[Y] = 0.66;

    vars.moveSpeed = 0.05;
	vars.rotSpeed = 0.05;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "01_mlx");
    mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, key_press, &vars);
    mlx_loop_hook(vars.mlx, rendering, &vars);
    mlx_loop(vars.mlx);
}