#!/usr/bin/env python3
for _ in range(int(input())):
    k = int(input())
    data = [input() for _ in range(k+1)]
    if 'pea soup' in data[1:-1] and 'pancakes' in data[1:]:
        print(data[0])
        break
else:
    print('anywhere is fine i guess')
