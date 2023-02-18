#!/usr/bin/env python3
(n, m) = list(map(int, input().split()))

P = [0]*(1<<n)
P[(1<<n)-1] = 1

for _ in range(m):
    (i, j, p) = input().split()
    i = int(i)-1
    j = int(j)-1
    p = float(p)
    X = 0
    while X < 1<<n:
        X |= (1<<i) | (1<<j)
        P[X & ~(1<<j)] += p*P[X]
        P[X] *= (1-p)
        X += 1

acc = [0]*n
for (X, q) in enumerate(P):
    for i in range(n):
        if X & (1<<i):
            acc[i] += q
print(('\n'.join('%.10f' % x for x in acc)))
