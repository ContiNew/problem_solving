import sys


def solve():
    N = int(input())  # 회의 참석자의 수
    M = int(input())  # 회의 참석자 끼리의 관계

    graph = [[sys.maxsize for i in range(N)] for j in range(N)]  # 인접 행렬 방식으로 그래프 구현
    for _ in range(M):
        src, dst = map(int, input().split(" "))  # 아는 사람 관계를 간선으로 입력
        src, dst = src - 1, dst - 1
        graph[src][dst] = 1
        graph[dst][src] = 1
    for x in range(M):
        graph[x][x] = 0  # 스스로에 대해서는 적용 안함

    for k in range(N):  # 플로이드 워셜 알고리즘
        for i in range(N):
            for j in range(N):
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])
