#!/usr/bin/python3

import sys
import random

default = {
    "n": 100,
    "height": 8,
}

def cmdlinearg(name):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    return default[name]


def main():              
    random.seed(int(sys.argv[-1]))
    n = int(cmdlinearg("n"))
    height = int(cmdlinearg("height"))
    maxx = 10**5
    points = []
    for y in range(0, 2*height+1):
        k = height-abs(height-y)+1
        S = set()
        for i in range(0,k):
            if len(points) == n:
                break
            x = random.randint(0,maxx)
            while x in S:
                x = random.randint(0,maxx)
            S.add(x)
            way = 2
            if i == 0:
                way = 1
            points.append([x, y, way])
    print(len(points))
    for p in points:
        print(p[0], p[1], p[2])
    
    
    
    
if __name__ == "__main__":
    main()

