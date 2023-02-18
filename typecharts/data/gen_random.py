#!/usr/bin/env python3
# arguments: n, m, probs (= probabilities for x, -, =)

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
pa, pb, pc = map(float, cmdlinearg('probs').split(','))
assert min(pa, pb, pc) >= 0
assert pa + pb + pc < 1 + 1e-9

mult = []
for _ in range(n):
    p = random.uniform(0, 1)
    if p < pa: mult.append(0)
    elif p < pa + pb: mult.append(0.5)
    elif p < pa + pb + pc: mult.append(1)
    else: mult.append(2)

outcome = {
    4   : '+',
    2   : '+',
    1   : '=',
    0.5 : '-',
    0.25: '-',
    0   : 'x'
}

print(n, m)
for i in range(m):
    a = random.randrange(n)
    b = random.randrange(n)
    print(a+1, b+1, outcome[mult[a] * mult[b]])
