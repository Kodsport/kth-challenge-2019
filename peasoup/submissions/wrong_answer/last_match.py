#!/usr/bin/env python3
res = 'anywhere is fine i guess'
for _ in range(int(input())):
    k = int(input())
    data = [input() for _ in range(k+1)]
    if 'pea soup' in data[1:] and 'pancakes' in data[1:]:
        res = data[0]
print(res)
