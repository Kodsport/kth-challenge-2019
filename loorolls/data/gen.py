#!/usr/bin/python3

import sys
import random

default = {
    "L": 31,
    "N": 6,
    "rand": 0,
    "maxl": 10**10
}

def cmdlinearg(name):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    return default[name]

def main():
    random.seed(int(sys.argv[-1]))
    L = int(cmdlinearg("L"))
    N = int(cmdlinearg("N"))
    rand = int(cmdlinearg("rand"))
    maxl = int(cmdlinearg("maxl"))

    if rand == 1:
        L = random.randint(1,maxl)
        N = random.randint(1,maxl)
        if L < N:
            L, N = N, L
    
    print(L,N)


if __name__ == "__main__":
    main()

