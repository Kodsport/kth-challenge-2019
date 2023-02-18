#!/usr/bin/env python3
n = int(input())
(_, Y, A) = list(zip(*[list(map(int, input().split())) for _ in range(n)]))

py = 1<<30
ans = 0
for (y, a) in reversed(sorted(zip(Y, A))):
    if y < py-1: c = 0
    if y < py:
        pc = c
        py = y
        c = 0
    if pc:
        pc -= 1
        a -= 1
        ans += 1
    if a: c += 1

print(ans)
