#!/usr/bin/python3

import sys
import random

default = {
    "n": 5,
    "m": 5,
    "land": 10,
}

def cmdlinearg(name):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    return default[name]

def main():
    random.seed(int(sys.argv[-1]))
    n = int(cmdlinearg("n"))
    m = int(cmdlinearg("m"))
    land = int(cmdlinearg("land"))

    cells = [(i,j) for i in range(0,n) for j in range(0,m)]
    grid = [['#' for j in range(0,m)] for i in range(0,n)]
    random.shuffle(cells)

    for i in range(0,land):
        grid[cells[i][0]][cells[i][1]] = '.'

    print(n,m)
    for i in range(0,n):
        print("".join(grid[i]))
    



if __name__ == "__main__":
    main()

