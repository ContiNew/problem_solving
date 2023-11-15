import math


def solve():
    array_size = int(input())
    array = list(map(int, input().split(" ")))
    domain_size = int(input())
    domain = list(map(int, input().split(" ")))

    array.sort()  # 어레이 정렬

    result = list()

    for d in domain:
        res = binary_search(array, d, 0, array_size - 1)
        result.append(res)

    for r in result:
        print(r)


def binary_search(arr: list, d: int, f: int, r: int):
    if f > r:
        return 0
    mid = math.floor((f + r) / 2)
    if arr[mid] > d:
        return binary_search(arr, d, f, mid - 1)
    elif arr[mid] < d:
        return binary_search(arr, d, mid + 1, r)
    else:
        return 1


solve()
