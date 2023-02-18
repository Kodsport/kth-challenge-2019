#!/usr/bin/env python3
(n, m) = list(map(int, input().split()))

P = [[0]*(1<<n) for _ in range(m+1)]
P[0][(1<<n)-1] = 1

for a in range(m):
    (i, j, p) = input().split()
    i = int(i)-1
    j = int(j)-1
    p = float(p)
    for (X, q) in enumerate(P[a]):
        if X & (1<<i) and X & (1<<j):
            P[a+1][X & ~(1<<j)] += p*q
            P[a+1][X] += (1-p)*q
        else:
            P[a+1][X] += q

acc = [0]*n
for (X, q) in enumerate(P[m]):
    for i in range(n):
        if X & (1<<i):
            acc[i] += q
print(('\n'.join('%.10f' % x for x in acc)))
