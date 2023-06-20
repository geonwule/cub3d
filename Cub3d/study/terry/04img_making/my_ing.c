#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

typedef struct s_img
{
    void    *img_ptr;
    int     *data;

    int     size_l;
    int     bpp;
    int     endian;
}   t_img;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win;

    int     x;
}   t_mlx;

int key_handler(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_ESC)
        exit(0);
    if (keycode == KEY_W)//Action when W key pressed
		mlx->x++;
	else if (keycode == KEY_S) //Action when S key pressed
		mlx->x--;

    printf("x: %d\n", mlx->x);
    return (0);
}

int main(void)
{
    t_mlx   *mlx = malloc(sizeof(t_mlx));
    int     count_w;
    int     count_h;
    t_img   img;

    mlx->x = 0;
    mlx->mlx_ptr = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "img_example");
    img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
    img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    //여기서 (int *)를 안해주고 img.data가 void *이면 밑에 배열값들을 참조할 때 다 4를 곱해야한다.
	//그렇기 때문에 int *로 캐스팅해주는편이 좋다고 한다.
	//keuhdall's github가면 더 자세한 내용을 볼 수 있습니다.

    count_h = -1;
    while (++count_h < IMG_HEIGHT)
    {
        count_w = -1;
        while (++count_w < IMG_HEIGHT)
        {
            if (count_w % 2) // 홀수
            {
                img.data[count_h * IMG_WIDTH + count_w] = 0x00FF00;
            }
            else
                img.data[count_h * IMG_WIDTH + count_w] = 0x0000FF;
        }
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 0, 0);
    mlx_hook(mlx->win, 2, 0, key_handler, mlx);
    mlx_loop(mlx->mlx_ptr);
    return (0);
}