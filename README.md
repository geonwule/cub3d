# cub3d
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

comment : 필요한 주석 추가 및 변경
rename : 파일 혹은 폴더명을 수정하거나 옮기는 작업만인 경우
remove : 파일을 삭제하는 작업만 수행한 경우
!HOTFIX : 급하게 치명적인 버그를 고쳐야 하는 경우



Subject

Type 과 함께 헤더를 구성합니다. 예를들어, 로그인 API 를 추가했다면 다음과 같이 구성할 수 있습니다.

ex) feat: Add login api

Body

헤더로 표현이 가능하다면 생략이 가능합니다. 아닌 경우에는 자세한 내용을 함께 적어 본문을 구성합니다.

Footer

어떠한 이슈에 대한 commit 인지 issue number 를 포함합니다. 위의 좋은 예시에서는 (#1) 처럼 포함시켰습니다. 그리고 close #1 처럼 close 를 통해 해당 이슈를 닫는 방법도 있습니다.

