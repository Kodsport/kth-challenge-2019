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
    Q = [(u, val)]
    while Q:
        (u, val) = Q.pop()
        if res[u] == effects[val]: continue
        if not poss[u] & (1<<val): return False
        res[u] = effects[val]
        for v in opp[u]:
            if res[v] != effects[4-val]:
                if val in [1,3] and res[v] == res[u]: return False
                Q.append((v, 4-val))
    return True

for (p, u) in sorted((poss[u], u) for u in range(1, n+1)):
    if res[u]: continue
    for i in [0,1,3,2]:
        if p & (1<<i):
            if not assign(u, i):
                assign(u, 2)
            break

import sys
sys.stdout.write('\n\t%s\t\t\n' % ''.join(res[1:]))
