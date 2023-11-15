
import sys

def solve():
    n = int(input())
    m = int(input())
    graph = [[sys.maxsize]*n for _ in range(n)] # 인접 행렬 방법
    for x in range(n): # 시작지와 도착지가 동일하면 가중치가 0
        graph[x][x]= 0
    for _ in range(m): # 초기 그래프 입력
        src, dst, weight = map(int,input().split(" "))
        src, dst = src-1, dst-1
        if(weight < graph[src][dst]):
            graph[src][dst] = weight
    
    for k in range(n): # 플로이드 워셜 알고리즘
        for i in range(n):
            for j in range(n):
               graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])
    
    for i in range(n):
        for j in range(n):
            if(graph[i][j]== sys.maxsize): print(0,end=" ")
            else: print(graph[i][j], end=" ")
        print()

solve()