import sys

a, b, c = map(int, sys.stdin.readline().rstrip().split(" "))


def pow(a, b, c):
    if b == 0:
        return 1
    if b == 1:
        return a % c
    # default case

    res = 0
    sav = pow(a, b // 2, c)
    if b % 2 == 0:
        res = (sav * sav) % c
    else:
        res = (sav * sav * a) % c

    return res


print(pow(a, b, c))
