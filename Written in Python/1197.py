# 그래프가 주어졌을 때, 그 그래프의 최소 스패닝 트리를 구해라
# 입력으로 정점의 개수 V, 간선의 갯수 E,
# 둘째 줄 부터 간선의 src, weight, dst 를 E 만큼 입력 받음
# 최소 스패닝 트리의 간선의 가중치는 음의 가중치도 가능하다.
# 출력으로 최소 스패닝 트리의 가중치를 출력한다.

import sys


def set_find(vertex: int, set_ids: list):
    return set_ids[vertex]


def set_union(v1: int, v2: int, set_ids: list):
    v1_id, v2_id = set_find(v1, set_ids), set_find(v2, set_ids)
    if v1_id == v2_id:
        return
    # 만약 v1, v2 가 같은 그룹이면 작업 해주지 않는다.
    else:
        for i in range(len(set_ids)):
            if set_ids[i] == v1_id:
                set_ids[i] = v2_id
    # v1, v2 가 다른 그룹이면, 더 작은 vertex의 set id로 통일해준다.


def solve():
    V_E = input().split(" ")  # 정점의 갯수, 간선의 갯수를 입력받음
    set_ids = [i for i in range(int(V_E[0]))]
    # kruskal 알고리즘을 위한 집합 id 리스트
    mst_weight = 0  # 출력으로 쓸 스패닝 트리의 가중치 합

    edges = []  # 입력 받은 간선들
    for i in range(int(V_E[1])):  # 간선의 갯수만큼 입력 받음
        edge = input().split(" ")
        for i in range(3):
            edge[i] = int(edge[i]) - 1
        edge[2] = edge[2] + 1

        edges.append(edge)
    edges.sort(key=lambda x: x[2])  # 가중치 기준으로 정렬

    for edge in edges:  # kruskal 알고리즘
        if set_find(edge[0], set_ids) == set_find(edge[1], set_ids):
            # cycle이 존재하면 병합하지 않는다.
            pass
        else:
            mst_weight += edge[2]
            set_union(edge[0], edge[1], set_ids)

    print(mst_weight)
    return


solve()
