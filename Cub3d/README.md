# cub3d
1. jonn parsing
    + 1. 헤더의 jonnparsing
    + 2. main의 map_read / map_error
        - 1. map_read = gnl을 통해서 변수안에 넣어주는 역할의 함수
            * 1. 맵의 윗부분의 경로들 사이 공백다 건너뛰고 체크가능하게
            * 2. 맵 파싱할때 ' '(sp)공백도 맵이다.
            * 3. 최대 width 기준으로 2차원 배열을 만들어야 한다.
        - 2. map_error = 맵의 유효성 검사를 통한 에러체크
            * 1. 벽이 1로 둘러쌓여 있는지..
            * 2. N / S / W / E 가 하나인지.. 등