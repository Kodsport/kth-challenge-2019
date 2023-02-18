#!/usr/bin/env python3
for _ in range(int(input())):
    k = int(input())
    data = [input() for _ in range(k+1)]
    if data[1:].count('pea soup') + data[1:].count('pancakes') >= 2:
        print(data[0])
        break
else:
    print('anywhere is fine i guess')
