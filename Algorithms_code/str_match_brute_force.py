

def string_match_with_brute_force(T:str, P:str)->int:
    for i in range (0, len(T)-len(P)): # i만큼 shift 한 경우에 대해서 테스트 한다. 
        j = 0 # 패턴에서 비교할 인덱스
        while j < len(P): # 패턴의 모든 문자를 비교할때 까지
            if T[i+j] != P[j]: break # 패턴이 일치 하지 않으면 바로 빠져나간다. 
            j += 1 # 일치 하는 경우, 다음 문자에 대해 비교한다. 
        if j == len(P): # 패턴의 모든 문자에 대해 일치하는 경우
            return i # i에서 패턴 매칭된다. 
    return -1 # 해당하는 부분 문자열을 찾지 못했을 경우 -1을 리턴한다.