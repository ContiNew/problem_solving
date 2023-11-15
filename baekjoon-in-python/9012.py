import sys
import collections

n = int(sys.stdin.readline().rstrip())

for _ in range(n):
    d = collections.deque()
    flag = False
    target = sys.stdin.readline().rstrip()
    for char in target:
        if char == "(":
            d.append(char)
        elif char == ")":
            if len(d) == 0:
                print("NO")
                flag = True
                break
            else:
                d.pop()
    if flag:
        continue
    if len(d) != 0:
        print("NO")
    else:
        print("YES")
