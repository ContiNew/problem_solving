seq = [1, 2, 3, 4]  # 입력
# 출력
# 1
# 2
# 3
# 4

# seq 변수에 접근 내용물을 확인해야한다
# 어떻게? -> seq가 리스트 변수
# -> 리스트의 내용물을 내가 어떻게 알더라?
# 1. 인덱싱 2. For 문 활용
# 1-1. 가능한 모든 인덱스를 활용해야한다. -> 0 ~ 원소수 -1 까지의 인덱스를 순회해아하겠구나
# -> 인덱스를 저장할 변수가 필요하겠구나, -> 한번 탐색이 끝나고 다음 인덱스로 가야겠구나 ( 각 반복마다 +1 해주면 되겠네 )
# 무한 반복을 어떻게 막지? -> 반복해야될 횟수가 시퀀스 길이만큼 -> 인덱스가 시퀀스 길이랑 똑같으면 그만두면 되겠다.

for item in seq:
    print(item)

i = 0
while i < len(seq):
    print(seq[i])
    i += 1