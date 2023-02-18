#!/usr/bin/python3

import sys
import random

default = {
    "n": 20,
    "maxy": 100,
    "maxway": 2,
}

def cmdlinearg(name):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    return default[name]

def main():
    random.seed(int(sys.argv[-1]))
    n = int(cmdlinearg("n"))
    maxy = int(cmdlinearg("maxy"))
    maxway = int(cmdlinearg("maxway"))
    maxx = 10**5
    S = set()
    print(n)
    for i in range(0,n):
        y = random.randint(0, maxy)
        x = random.randint(0, maxx)
        while x*(maxy+1)+y in S:
            y = random.randint(0, maxy)
            x = random.randint(0, maxx)
        S.add(x*(maxy+1)+y)
        print(x,y,random.randint(1,maxway))
        

    
    



if __name__ == "__main__":
    main()

