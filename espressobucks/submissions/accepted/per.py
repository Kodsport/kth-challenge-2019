#!/usr/bin/env python3
(n, m) = list(map(int, input().split()))
grid = ['#'*(m+2)] + ['#' + input() + '#' for _ in range(n)] + ['#'*(m+2)]
for i in range(1, n+1):
    grid[i] = list(grid[i])
    for j in range(1, m+1):
        if grid[i][j] == '.' and ((i+j) % 2 or (grid[i-1][j] == '#' and grid[i][j-1] == '#' and grid[i+1][j] == '#' and grid[i][j+1] == '#')):
            grid[i][j] = 'E'
    print((''.join(grid[i][1:-1])))
