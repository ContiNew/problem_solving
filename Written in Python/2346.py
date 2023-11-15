import collections

n = int(input())
seq = [int(n) for n in input().split()] 

q = collections.deque(seq)
idx_map = dict()
for i, e in enumerate(seq):
    idx_map[e] = i+1
res = []

while len(q) != 0:
   k = q.popleft()
   if k > 0:
       remain = k
       while remain != 0:
           tmp = q.popleft()
           remain -= 1
           q.append(tmp)
       target = q.popleft()
       res.append(idx_map[target])
       k = target
   else:
       remain = k
       while remain != 0:
           tmp = q.pop()
           remain += 1
           q.appendleft(tmp)
       target = q.popleft()
       res.append(idx_map[target])
       k = target
       
           
        
print(" ".join([str(n) for n in res]))