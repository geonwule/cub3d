CUB3D

0. 개요
    + 1. 레이캐스팅을 이용하여 2D를 3D처럼 시점에 따라서 map_set을 하여 표시해야함

1. 공부
    + 1. 대략적인 파싱 완료
    + 2. 대략적인 창 뜨기 완료
    + 3. 대략적인 미니맵 구상
        - 1. mlx_new_image로 새로운 img_ptr을 하나 생성 [HEIGHT] x [WIDTH] 
        - 2. (int *)mlx_get_data_addr로 (int *)data배열에 저장함.
        - 3. data[HEIGHT x WIDTH] 일차원 배열에 각각의 부분에 색상을 넣으면 새로운 이미지가 생김
        - 4. WIDTH, HEIGHT를 맵을 파싱후에 넣어준다.
        - 5. 그 후 맵의 1인 경우 a색상, 맵이 0인경우 b색상, 맵이 player인경우 c색상을 삽입

2. mlx 주요 함수 / <mlx.h> / mlx_init(), mlx_new_window(), mlx_new_image(), mlx_get_data_addr(), mlx_put_image_to_window(), mlx_xpm_file_to_image(),  mlx_key_hook(), mlx_hook(), mlx_loop_hook(), mlx_loop()
    + 1. mlx_init
        - 1. 형태 : void *mlx_init();
        - 2. 인수 : void
        - 3. 반환값 : mlx연결에 대한 포인터 (void *)
        - 4. 쓰임 : mlx 연결을 초기화 하고 연결에 대한 포인터를 반환, 다른 mlx함수들을 사용하기전에 초기화를 꼭 해야하고, 이 포인터를 주로 인수로 씀.
    + 2. mlx_new_window
        - 1. 형태 : void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);
        - 2. 인수 :
            - mlx_ptr : mlx포인터
            - width : 윈도우 가로크기 (int)
            - height : 윈도우 세로크기 (int)
            - title : 윈도우 제목
        - 3. 반환값 : 윈도우에 대한 포인터
        - 4. 쓰임 : 새로운 윈도우를 생성하고 해당 윈도우 포인터를 반환, mlx_ptr과 마찬가지로 다른 mlx함수의
        인수로 쓰이는 경우 많음
    + 3. mlx_new_image
        - 1. 형태 : void *mlx_new_image(void *mlx_ptr, int width, int height);
        - 2. 인수 :
            - mlx_ptr : mlx포인터
            - width : 이미지 가로크기 (int)
            - height : 이미지 세로크기 (int)
        - 3. 반환값 : 이미지에 대한 포인터 (void *)
        - 4. 쓰임 : 새로운 이미지를 생성하고 해당 이미지 포인터를 반환, 다른 mlx함수의 인수로 쓰이는 경우 많음
    + 4. mlx_get_data_addr
        - 1. 형태 : char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
        - 2. 인수 :
            - img_ptr : 이미지 포인터
            - bits_per_pixel : 픽셀당 비트수를 저장할 변수의 포인터(int *), 보통 &bits식의 인트값의 주솟값을 넣고 해당값이 지정되어 나오는 형식
            - size_line : 한줄의 픽셀 데이터 크기를 저장할 변수의 포인터
            - endian : 시스템의 엔디안 정보를 저장할 변수의 포인터
        - 3. 반환값 : 이미지 데이터에 대한 포인터 (char *)
        - 4. 쓰임 : 이미지 데이터에 대한 포인터를 반환하고 해당 이미지의 픽셀당 비트수, 한줄의 픽셀 데이터 크기, 시스템의 엔디안 정보를 인수로 전달한 변수들에 저장합니다. / 데이터를 char형 배열로 반환받아서,
        인덱스마다 픽셀단위로 색깔을 지정하는등 할수있음.
    + 5.  mlx_put_image_to_window
        - 1. 형태 : int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
        - 2. 인수 :
            - mlx_ptr : mlx포인터
            - win_ptr : win포인터
            - img_ptr : img포인터
            - x : 이미지를 표시할 윈도우 내의 x좌표 (int)
            - y : 이미지를 표시할 윈도우 내 y 좌표 (int)
        - 3. 반환값 : 함수의 성공 여부를 나타내는 정수 (0 또는 -1)
        - 4. 쓰임 : 지정한 위치(x, y)좌표에 이미지를 윈도우에 표시합니다. 해당 윈도우에 대한 포인터와 이미지에 대한 포인터를 사용합니다.
    + 6. mlx_xpm_file_to_image
        - 1. 형태 : void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
        - 2. 인수 :
            - mlx_ptr : mlx포인터
            - filename : xpm파일 경로 및 이름(주로 상대경로 쓰임)
            - width : 이미지의 가로 크기를 저장할 변수의 포인터(int *)
            - height : 이미지 세로 크기를 저장할 변수의 포인터(int *)
        - 3. 반환값 : 이미지에 대한 포인터 / void *mlx_new_image()와 마찬가지로 xpm파일을 넣은 이미지 포인터를 반환 받는 것임.
        - 4. 쓰임 : xpm파일을 로드하여 이미지를 생성하고 포인터를 반환받는다. 이미지 가로 세로 크기는 전달된 변수에 저장한다.
    + 7. mlx_key_hook
        - 1. 형태 : int mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param)
        - 2. 인수 :
            - win_ptr : win포인터
            - funct_ptr : 키 이벤트를 처리하는 함수
            - param 함수에 전달할 매개변수 (void *)
        - 3. 반환값 : 성공여부 판단 (0 또는 -1)
        - 4. 쓰임 : 윈도우에서 키이벤트가 발생할때 호출할 함수를 등록, 이벤트가 발생하면 해당 함수 호출되며, 이벤트에 대한 정보와 전달된 매개변수를 처리할 수 있습니다.
    + 8. mlx_hook
        - 1. 형태 : int mlx_hook(void *win_ptr, int event, int event_mask, int(*funct_ptr)(), void *param)
        - 2. 인수 :
            - win_ptr : win포인터
            - event : 이벤트 종류를 나타내는 정수
            - event_mask : 이벤트를 처리할 마스크 값
            - funct_ptr : 이벤트를 처리하는 함수 포인터
            - param : 함수에 전달할 매개변수
        - 3. 반환값 : 성공시 0 , 실패시 -1
        - 4. 쓰임 : 윈도우에서 지정된 이벤트가 발생할때 호출할 함수 등록, 이벤트에 대한 정보와 전달된 매개변수를 처리 할 수 있다.
        - 5. event_mask를 넣는 이유 ?
        : mlx_hook(vars->win, 6, 1L << 6, handle_mouse_move, vars);
        -> mlx창 내부에서만 마우스 무브가 인정되어 산출됨
          mlx_hook(vars->win, 6, 0, handle_mouse_move, vars);
        -> mlx창 외부도 마우스 무브가 인정되어 산출됨

    + 9. mlx_loop_hook
        - 1. 형태 : int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
        - 2. 인수 :
            - mlx_ptr : mlx 포인터
            - funct_ptr : 반복적으로 실행되는 함수의 포인터
            - param : 함수에 전달할 매개변수
        - 3. 반환값 : 함수의 성공여부를 나타내는 정수 0, -1
        - 4. 쓰임 : mlx이벤트 루프가 실행되는 동안 지속적으로 호출되는 함수를 등록합니다. 이 함수는 반복적으로 수행할 작업이 있는 경우 사용됩니다.
        - 5. 추가내용 / 시뮬레이션: 그래픽 시뮬레이션을 만들 때, mlx_loop_hook()를 사용하여 시뮬레이션 상태를 갱신하고 화면을 업데이트할 수 있습니다. 등록된 핸들러 함수에서 시뮬레이션 로직을 실행하고 그래픽을 갱신하여 시뮬레이션의 진행 상황을 시각적으로 표시할 수 있습니다.
    + 10. mlx_loop
        - 1. 형태 : void mlx_loop(void *mlx_ptr);
        - 2. 인수 : mlx_ptr 
        - 3. 반환값 : void
        - 4. 쓰임 : mlx 이벤트 루프를 시작합니다. 등록된 이벤트 핸들러 함수들이 호출되고, 그래픽 애플리케이션이 이벤트에 응답하며 반응성을 유지합니다. 이 함수는 일반적으로 프로그램의 마지막에 호출됩니다.
    + 8. 
        - 1. 형태 :
        - 2. 인수 :
        - 3. 반환값 :
        - 4. 쓰임 :

3. 진행상황
    + 1. (6. 2.금)
        - 1. 함수들 기능별 폴더정리, makefile정리 완료
        - 2. mlx_hook의 key_press, key_release, mouse_button, mouse_move의 기능별 이벤트 정리 완료
            - 추후에 레이케스팅 공부 후 핸들러 함수들 보완 예정
        - 3. mlx_loop_hook()함수 생성하여 이벤트시 계속 업데이트 해주는 rendering함수를 실행
            - key 또는 mouse 이벤트가 발생 할때마다 rendering을 호출하여 화면을 업데이트 해주는 방식임
            - 예를들어 마우스로 총을 쏘는 모션 mouse_event가 발생하면 누르는 순간 렌더링
            - 키보드로 왼쪽 누르는 순간 렌더링, 떼는순간 렌더링
        - 4. 현재는 맵을 터미널에 출력하여 키보드 이벤트가 생기면 플레이어가 이동하게만 구현한 상태
        - 5. 추후에 레이케스팅으로 플레이어 위치에서 1인칭 시점의 이미지를 렌더링 하면 될듯..
        - 6. 맵 파싱부분에서 맵을 1차원 배열에서 연결리스트로 바꿈 
            - 이유는 이동시에 라인별로 연결해두었기 떄문에 바로 위로 이동 아래로 이동시에 편리...
            - 이전에는 계산을 일일히 해줘야 했음
    + 2. (6. 3. 토)
        - 1. 미니맵 구현완료.
            - 미니맵 처음에는 픽셀단위 컬러로 찍으려 했으나, so_long아이디어 가져와서
            10x10사이즈의 xpm을 가져와 map사이즈만큼 왼쪽 상단에 출력
            - 미니맵도 mlx_loop_hook()의 rendering에서 map_set(3D출력부분) 이후 그위에 덮어서
            mini_map()을 띄우는 원리
        - 2. 이제 레이캐스팅 이용해서 3D 부분만 띄우면 됌
        - 3. 그전에 먼저 ceiling과, floor을 먼저 해보자, rendering에서 map_set()전에 넣으면 됌.
        - 4. 일단 fill_back_ground로 위 아래 구분지어서 색 넣긴 했으나 공부 필요.
            - argb, dst = vars->data + (i * (vars->size_l) + j * (vars->bpp) / 8); 등.

    + 3. (6.14. 수)
        - 1. 왜 튜토리얼처럼 안되나 했더니... 튜토리얼은 int 배열,
        나는 char 배열이다.. 그런데
        if (map[mapX][mapY] > 0) 이렇게 정수형으로 표현되어있는 튜토리얼을 그대로 따라했으니 될리가 없다..
        if (map[mapX][mapY] != '0') 이렇게 문자열로 수정했더니
        된다...

        - 2. 이제 적용은 해보았으니 이해하고, xpm파일로 대체 해야한다..
        동, 서, 남, 북 구분지어서.

    + 4. (6.15. thursday)
        - 1. 내꺼는 렌더링이 너무 느리다 -> mlx_put_pixel이 비효율적이여서 그런거 같다.
        -> img.data[]에 texture이미지를 배열로 구분해서 넣고
        -> mlx_put_image_to_window 를 한다
        -> study 04_floor_ceiling부분 참조해서 해보자.

* mlx_공부 사이트 : https://love-every-moment.tistory.com/62
* racasting_공부 사이트 : https://github.com/365kim/raycasting_tutorial
* raycasting_게임 사이트 : http://users.atw.hu/wolf3d/
