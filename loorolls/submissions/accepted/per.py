#!/usr/bin/env python3
def ans(l, n):
    k = 1
    while l % n:
        n -= l % n
        k += 1
    return k
(l, n) = list(map(int, input().split()))
print((ans(l, n)))

