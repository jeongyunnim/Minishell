- [ ] 명령어를 입력받을 때 prompt를 표시해야 함
- [ ] working history를 가지고 있어야 함.
- [ ] 올바른 실행 파일을 검색하고 실행해야 함(PATH변수를 기반으로 하거나 상대경로, 절대경로를 사용).
- [ ] 1개의 전역변수만 사용 가능하다. 사용 목적을 설명할 수 있어야 한다.
- [ ] 닫히지 않은 따옴표 (’ 또는 “) 또는 과제에서 요구하지 않는 특수문자(\ 또는 ;)를 해석하지 않는다.
- [ ] ‘ : 셸은 ‘로 묶인 시퀀스의 메타문자를 해석하면 안 된다.
- [ ] “ : 셸은 “로 묶인 시퀀스 내의 메타문자를 $기호를 제외하고 해석하면 안 된다.
- [ ] redirection을 구현해야 한다.
    - [ ] < input으로 redirect되어야 한다.
    - [ ] > output으로 redirect되어야 한다.
    - [ ] << 주어진 구분 기호가 포함된 줄이 표시될 때까지 입력을 읽어야 한다. 하지만 history를 업데이트 할 필요는 없다.
        - 예시
            
            ```bash
            echo "Please enter some input, followed by a line containing only 'EOF':"
            
            # Use the << operator to specify the delimiter
            # In this case, we're using "EOF" as the delimiter
            # The user can enter any text they want until they enter a line containing only "EOF"
            cat << EOF
            $(tput bold)
            This is some sample input.
            It can contain multiple lines.
            When you're finished, enter a line containing only 'EOF'.
            $(tput sgr0)
            EOF
            
            echo "Input complete!"
            ```
            
    - >> append mode에서 출력을 redirection 해야한다.
- [ ] pipe ‘|’를 구현해야 한다. 각 명령의 출력을 다른 명령의 입력에 연결한다. 이 연산자를 이용하여 복잡한 작업을 수행할 수 있다.
- [ ] 환경 변수($ 뒤의 일련의 문자)가 그 값으로 확장되도록 처리해야한다.
- [ ] $? 을 입력받으면 최근 실행된 가장 최신의 파이프라인의 exit의 상태로 확장되도록 해야한다.
- [ ] ctrl-C, ctrl-D, ctrl-\ 의 행동을 bash와 동일하게 처리해야 한다.
    - [ ] ctrl-C: SIGINT
    - [ ] ctrl-D: EOF
    - [ ] ctrl-\: SIGQUIT
- [ ] bash의 interactive 모드: 사용자가 셸에 명령을 입력하고 피드백을 받을 수 있는 CLI 모드
    - [ ] ctrl-C: 새로운 줄에 프롬프트를 반환해야 함.
    - [ ] ctrl-D: shell을 종료한다.
    - [ ] ctrl-\: 아무 일도 하지 않는다.
- [ ] 아래의 builtin을 구현해야한다.
    - [ ] **echo** -n 옵션
    - [ ] **cd** 상대 경로 또는 절대 경로만 있음.
    - [ ] **pwd** with no options
    - [ ] **export** with no options
    - [ ] **unset** with no options
    - [ ] **env** 옵션 또는 인자 없음
    - [ ] **exit** with no options