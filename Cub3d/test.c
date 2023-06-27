#include "./mlx_opengl/mlx.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_ray
{
    double angle;
    double distance;
} t_ray;

typedef struct s_game
{
    void *mlx;
    void *window;
    double player_x;
    double player_y;
    double player_angle;
    t_ray rays[WIDTH];
} t_game;

int handle_key_press(int keycode, t_game *game)
{
    // 키 이벤트 처리 로직
    return (0);
}

void cast_rays(t_game *game)
{
    for (int x = 0; x < WIDTH; x++)
    {
        double ray_angle = game->player_angle - atan((x - WIDTH / 2) / HEIGHT / 2);
        game->rays[x].angle = ray_angle;
        // 충돌 감지 로직 및 거리 계산
        // ...
    }
}

void render(t_game *game)
{
    // 화면 그리기 로직
    // ...
}

int main(void)
{
    t_game game;

    // mlx 초기화
    game.mlx = mlx_init();
    game.window = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Raycasting Example");

    // 게임 초기화
    game.player_x = WIDTH / 2;
    game.player_y = HEIGHT / 2;
    game.player_angle = 0;

    // 이벤트 핸들러 등록
    mlx_hook(game.window, 2, 0, handle_key_press, &game);

    // 메인 루프
    mlx_loop_hook(game.mlx, cast_rays, &game);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);

    return (0);
}
