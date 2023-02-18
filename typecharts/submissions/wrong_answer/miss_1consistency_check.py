#!/usr/bin/env python3
effects = 'x-=+'
mask = [15, 6, 14, 12]

(n, m) = list(map(int, input().split()))
poss = [15]*(n+1)
opp = [[] for _ in range(n+1)]
for _ in range(m):
    line = input().split()
    (u, v) = list(map(int, line[:2]))
    f = effects.index(line[2])
    poss[u] &= mask[f]
    poss[v] &= mask[f]
    if f == 2:
        opp[u].append(v)
        opp[v].append(u)

res = [None]*(n+1)

def assign(u, val):
    res[u] = effects[val]
    for v in opp[u]:
        if res[v] != effects[4-val] and (val in [1,3] and res[v] == res[u] or not assign(v, 4-val)):
            return False
    return True

for (p, u) in sorted((poss[u], u) for u in range(1, n+1)):
    if res[u]: continue
    for i in [0,1,3,2]:
        if p & (1<<i):
            if not assign(u, i):
                assign(u, 2)
            break

print(''.join(res[1:]))
