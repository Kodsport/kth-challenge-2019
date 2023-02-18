#!/usr/bin/env python3
big = 10**5 + 1
n = int(input())

counts = [[0]*big for _ in range(2)]
for lift in range(n):
    x, y, a = list(map(int, input().split()))
    counts[a-1][y] += 1

last = 0
total = 0
for row in range(big-1):
    # Greedily take largest match
    up = (counts[0][row] - last) + counts[1][row]
    down = counts[0][row+1] + counts[1][row+1]
    use = min(up,down)
    last = max(use - counts[1][row+1], 0)
    total += use

print(total)
