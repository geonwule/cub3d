# cub3d(geon)
1. 6.23.(금)
    + feat: 죽었을때 P누르면 부활(리셋), ESC누르면 종료
    + feat: 난수(random_generator)구현, 몬스터리젠/포션드랍률 설정
    + feat: 스피드 조절기능(q, e), 몬스터 포션드랍(체력충전)
    + 할 일
        - mandatory의 벽 사분면 구분해서 출력하는것
        - ray_casting, sprite 개념 이해

2. 6.24.(Sat)
    + feat: 몬스터 점프 구현(sprite up & down)
    + feat: 벽 텍스쳐 방면에 따라 구분(N,S,E,W)
    + chore: Texture 수정(북쪽, 문)
    + docs: mlx_function 추가/Segfault방지(ft_xpm, ft_get_addr)
    + feat: 몬스터 뜨기 전 경고메세지 추가(warning message), 깜빡거림

# rule
Commit message 7가지 규칙
제목과 본문을 한 줄 띄어 구분
제목은 50자 이내
제목 첫 글자는 대문자
제목 끝에 마침표 X
제목은 명령문으로, 과거형 X
본문의 각 행은 72자 이내 (줄바꿈 사용)
본문은 어떻게 보다 무엇을, 왜에 대하여 설명
Commit message 구조
기본적으로 commit message 는 제목, 본문, 꼬리말로 구성합니다.
제목은 필수사항이며, 본문과 꼬리말은 선택사항입니다.

<type>: <subject>

<body>

<footer>

Type

memo : 메세지
feat : 새로운 기능 추가, 기존의 기능을 요구 사항에 맞추어 수정
fix : 기능에 대한 버그 수정
build : 빌드 관련 수정
chore : 패키지 매니저 수정, 그 외 기타 수정 ex) .gitignore
ci : CI 관련 설정 수정
docs : 문서(주석) 수정
style : 코드 스타일, 포맷팅에 대한 수정
refactor : 기능의 변화가 아닌 코드 리팩터링 ex) 변수 이름 변경
test : 테스트 코드 추가/수정
release : 버전 릴리즈


Subject

Type 과 함께 헤더를 구성합니다. 예를들어, 로그인 API 를 추가했다면 다음과 같이 구성할 수 있습니다.

ex) feat: Add login api

Body

헤더로 표현이 가능하다면 생략이 가능합니다. 아닌 경우에는 자세한 내용을 함께 적어 본문을 구성합니다.

Footer

어떠한 이슈에 대한 commit 인지 issue number 를 포함합니다. 위의 좋은 예시에서는 (#1) 처럼 포함시켰습니다. 그리고 close #1 처럼 close 를 통해 해당 이슈를 닫는 방법도 있습니다.

