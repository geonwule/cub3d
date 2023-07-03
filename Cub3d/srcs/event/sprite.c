#include "cub3d.h"

static int	check_sprite_num(t_vars *vars, char **map, int height, int width)
{
	int	i;
	int	j;

	vars->sprite_num = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'M' || map[i][j] == 'P' || map[i][j] == 'H')
				vars->sprite_num++;
			j++;
		}
		i++;
	}
	if (vars->sprite_num == 0)
		return (0);
	return (1);
}

static t_sprite	*malloc_sprite(t_vars *vars, int s_idx, int i, int j)
{
	t_sprite	*sprite;

	sprite = ft_malloc(sizeof(t_sprite) * vars->sprite_num);
	i = -1;
	s_idx = 0;
	while (++i < vars->map.height)
	{
		j = -1;
		while (++j < vars->map.width)
		{
			if (vars->map.arr[i][j] == 'M')
				sprite[s_idx].texture = TEX_MONSTER;
			else if (vars->map.arr[i][j] == 'P')
				sprite[s_idx].texture = TEX_POTION;
			else if (vars->map.arr[i][j] == 'H')
				sprite[s_idx].texture = TEX_NPC;
			else
				continue ;
			sprite[s_idx].x = (double)i + 0.5;
			sprite[s_idx].y = (double)j + 0.5;
			s_idx++;
		}
	}
	return (sprite);
}

static void	sprite_init(t_vars *vars, char **map)
{

	if (!check_sprite_num(vars, map, vars->map.height, vars->map.width))
		return ;
	if (vars->sprite)
		free(vars->sprite);
	vars->sprite = malloc_sprite(vars, 0, -1, -1);
	//sprite_up_and_down
	if (vars->v_move >= 300 || vars->v_move <= 0)
		vars->v_i *= -1;
	vars->v_move += vars->v_i;

}

static void	sortSprites(int *order, double *dist, int amount)
{
	double	tmp_dist;
	int		tmp_idx;
	int		i;
	int		j;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_dist = dist[j];
				tmp_idx = order[j];
				dist[j] = dist[j + 1];
				order[j] = order[j + 1];
				dist[j + 1] = tmp_dist;
				order[j + 1] = tmp_idx;
			}
		}
	}
}

static void	sprite_ex(t_vars *vars, t_sprite *sprite)
{
	int		spriteOrder[vars->sprite_num];
	double	spriteDistance[vars->sprite_num];
	t_info	*info = vars->info;
	
	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < vars->sprite_num; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((info->posX - sprite[i].x) * (info->posX - sprite[i].x) \
			+ (info->posY - sprite[i].y) * (info->posY - sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, vars->sprite_num);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < vars->sprite_num; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - info->posX;
		double spriteY = sprite[spriteOrder[i]].y - info->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1.5
		#define vDiv 1.5
		// #define vMove 200.0 // 64 ~ 200
		// -> sprite->v_move
		int vMoveScreen = (int)(vars->v_move / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = (int)fabs((WIN_HEIGHT / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
		if(drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = (int)fabs((WIN_HEIGHT / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
				int color = info->texture[sprite[spriteOrder[i]].texture][TEX_WIDTH * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
}

void	sprite(t_vars *vars)
{
	sprite_init(vars, vars->map.arr);
	if (vars->sprite)
		sprite_ex(vars, vars->sprite);
}