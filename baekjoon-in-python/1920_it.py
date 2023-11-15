import math


def solve():
    array_size = int(input())
    array = list(map(int, input().split(" ")))
    domain_size = int(input())
    domain = list(map(int, input().split(" ")))

    array.sort()  # 어레이 정렬

    for d in domain:
        front, rear = 0, array_size - 1
        while 1:
            if front > rear:
                print(0)
                break
            mid = math.floor((front + rear) / 2)
            if array[mid] > d:
                rear = mid - 1
            elif array[mid] < d:
                front = mid + 1
            else:
                print(1)
                break


solve()
