#!/usr/bin/env pypy
import os
import random
import sys

MAX_N = 15
MAX_M = 1000

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), '../data/secret')

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '-' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(n, attempts, short_desc=None, long_desc=None):
    f = next_file(short_desc=short_desc, long_desc=long_desc)
    f.write('%d %d\n' % (n, len(attempts)))
    for (i, j, p) in attempts:
        f.write('%d %d %.6f\n' % (i, j, p))
    f.close()


def gen_random(n, m, min_p=0, max_p=1, short_desc=None):
    attempts = []
    for _ in range(m):
        (i, j) = random.sample(range(1, n+1), 2)
        p = random.uniform(min_p, max_p)
        attempts.append((i, j, p))
    if short_desc is None:
        short_desc='random_n%d_m%d_prange%.2fto%.2f' % (n, m, min_p, max_p)
    save_case(n, attempts, short_desc=short_desc)
    
def main():
    random.seed(2019)

    gen_random(1, 0, short_desc='n1')
    gen_random(MAX_N, 0, short_desc='m0')

    for _ in range(10):
        n = random.randint(2, MAX_N)
        m = random.randint(1, MAX_M)
        min_p = random.random()
        max_p = random.random()
        if min_p > max_p: (min_p, max_p) = (max_p, min_p)
        gen_random(n, m, min_p, max_p)
    
    gen_random(MAX_N, MAX_M)
    gen_random(MAX_N, MAX_M, max_p=0.1)
    gen_random(MAX_N, MAX_M, max_p=0.1)
    gen_random(MAX_N, MAX_M, max_p=0.001)
    gen_random(MAX_N, MAX_M, max_p=0, short_desc='incompetent_assassins')
    gen_random(MAX_N, MAX_M, min_p=1, short_desc='flawless_assassins')

if __name__=='__main__':
    main()
