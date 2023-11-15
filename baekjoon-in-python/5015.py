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


def KMP_match(T: str, P: str) -> int:
    F = [0 for _ in range(len(P))]
    failure_function(P, F)  # 전처리 수행
    i, j = 0, 0  # i 는 T에서의 위치, j는 P에서의 위치
    while i < len(T):
        if P[j] == "*":
            if P[j + 1] != T[i]:
                i = i + 1
                continue
            else:
                j = j + 1
        if T[i] == P[j]:  # 현재 위치에서 매칭 발생
            if j == len(P) - 1:  # 패턴의 마지막 까지 일치할 경우
                return i - j  # 패턴에서 일치하는 곳을 리턴해줌
            i = i + 1
            j = j + 1  # 아닌 경우 다음 위치에 대해서 비교
        elif j > 0:  # 맨처음이 아닌 위치에서 불일치가 발생할 경우
            j = F[j - 1]  # 현 위치 기준에서 매칭된 가장 긴 suffix 와 일치하는 prefix 만큼 밀어준다.
        else:
            i = i + 1  # 처음부터 맞지 않는 경우 한칸 shift
    return -1  # 일치하지 않는 경우 -1을 리턴한다.


def solve():
    P = input()  # 패턴
    count = int(input())  # 파일 갯수
    files = []
    result = []
    for _ in range(count):
        files.append(input())

    for file in files:
        flag = 0
        if len(file) < len(P):
            flag = KMP_match(P, file)
        else:
            flag = KMP_match(file, P)
        if flag != -1:
            result.append(file)

    print("\n".join(result))


solve()
