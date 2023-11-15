import collections


n, k = map(int , input().split(" "))

q = collections.deque(range(1,n+1))
res = []

while len(q) != 0:
    counter = 0
    while counter != k:
        fv = q.popleft()
        counter += 1
        if counter == k:
            res.append(fv)
            break
        q.append(fv)

print("<"+", ".join([str(n) for n in res])+">")