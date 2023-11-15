import sys
import collections

n, k = map(int, sys.stdin.readline().rstrip().split(" "))

d = collections.deque(range(1, n + 1))
d = collections.deque()
