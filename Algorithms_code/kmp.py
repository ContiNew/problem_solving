def failure_function(P: str, F: list):
    F[0] = 0  # P[1..0] 은 정의 되지 않는다.
    i = 1  # suffix 를 구하기 위해 사용
    j = 0  # prefix를 구하기 위해 사용
    while i < len(P):  # 패턴 전체에 대해서 반복
        if P[i] == P[j]:
            # 이시점에서 j+1개의 문자들이 매치됨
            F[i] = j + 1  # 이 시점에서 리스트에 기록한다.
            i += 1
            j += 1  # 다음 위치에 대해서 매칭 여부 확인
        elif j > 0:  # 매칭되지 않았을 때, 실패함수를 통해 P를 Shift
            j = F[j - 1]
        else:
            F[i] = 0  # 시작부터 매칭되지 않을 경우,
            i += 1  # 다음 위치에서 부터 검증
