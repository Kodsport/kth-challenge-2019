#!/usr/bin/env python3
peasoup = False
pancakes = False
for _ in range(int(input())):
    k = int(input())
    data = [input() for _ in range(k+1)]
    peasoup |= 'pea soup' in data[1:]
    pancakes |= 'pancakes' in data[1:]
    if peasoup and pancakes:
        print(data[0])
        break
else:
    print('anywhere is fine i guess')
