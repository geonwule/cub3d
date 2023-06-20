#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 720
#define HEIGHT 480
#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17
#define X 0
#define Y 1

typedef struct s_vars
{
    void    *mlx;
	void	*win;
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	moveSpeed;
	double	rotSpeed;
	
}   t_vars;