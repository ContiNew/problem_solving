import sys
import collections

d = collections.deque()

n = int(sys.stdin.readline().rstrip())

for _ in range(n):
    command = sys.stdin.readline().rstrip()
    cmd = command.split(" ")
    if cmd[0] == "push_front":
        d.appendleft(cmd[1])
    elif cmd[0] == "push_back":
        d.append(cmd[1])
    elif cmd[0] == "pop_front":
        if len(d) == 0:
            print(-1)
        else:
            erased = d.popleft()
            print(erased)
    elif cmd[0] == "pop_back":
        if len(d) == 0:
            print(-1)
        else:
            erased = d.pop()
            print(erased)
    elif cmd[0] == "back":
        if len(d) == 0:
            print(-1)
        else:
            erased = d.pop()
            print(erased)
            d.append(erased)
    elif cmd[0] == "front":
        if len(d) == 0:
            print(-1)
        else:
            erased = d.popleft()
            print(erased)
            d.appendleft(erased)
    elif cmd[0] == "empty":
        if len(d) == 0:
            print(1)
        else:
            print(0)
    else:
        print(len(d))
