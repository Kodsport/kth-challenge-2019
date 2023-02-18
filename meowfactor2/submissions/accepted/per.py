#!/usr/bin/env python3
import re

def gen(P, steps, res):
    res[steps].add(''.join(P).strip('.'))
    if steps + 1 < 4:
        for i in range(len(P)):
            gen(P[:i] + P[i+1:], steps+1, res) # del
            gen(P[:i] + ['.'] + P[i:], steps+1, res) # ins
            gen(P[:i] + ['.'] + P[i+1:], steps+1, res) # sub
            if i:
                gen(P[:i-1] + [P[i], P[i-1]] + P[i+1:], steps+1, res) # swap
        
res = [set() for _ in range(4)]
gen(list('meow'), 0, res)
for i in range(4):
    res[i] = re.compile('|'.join(res[i]))

S = input()
print((min([i for i in range(4) if res[i].search(S)] + [4])))
