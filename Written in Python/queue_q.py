import sys

stack = []
size = 0

n = int(sys.stdin.readline().rstrip())

for _ in range(n):
    command = sys.stdin.readline().rstrip()
    cmd = command.split(" ")
    if cmd[0] == "push":
        stack.append(cmd[1])
        size += 1
    elif cmd[0] == "pop":
        if size == 0:
            print(-1)
        else:
            erased = stack[0]
            del stack[0]
            print(erased)
            size -= 1
    elif cmd[0] == "back":
        if size == 0:
            print(-1)
        else:
            back = stack[size - 1]
            print(back)
    elif cmd[0] == "front":
        if size == 0:
            print(-1)
        else:
            front = stack[0]
            print(front)
    elif cmd[0] == "empty":
        if size == 0:
            print(1)
        else:
            print(0)
    else:
        print(size)
