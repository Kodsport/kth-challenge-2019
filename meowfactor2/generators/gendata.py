#!/usr/bin/env pypy
import os
import random
import sys

MAX_LEN = 10**6

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

def save_case(S, short_desc=None, long_desc=None):
    f = next_file(short_desc=short_desc, long_desc=long_desc)
    f.write('%s\n' % S)
    f.close()


def gen(P, steps, res):
    res[steps].add(''.join(P).strip('.'))
    if steps + 1 < 4:
        for i in range(len(P)):
            gen(P[:i] + P[i+1:], steps+1, res) # del
            gen(P[:i] + ['.'] + P[i:], steps+1, res) # ins
            gen(P[:i] + ['.'] + P[i+1:], steps+1, res) # sub
            if i:
                gen(P[:i-1] + [P[i], P[i-1]] + P[i+1:], steps+1, res) # swap
        
def simplify(res):
    for i in range(4):
        for j in range(i):
            res[i] = res[i] - res[j]
    for i in range(4):
        nres = set()
        for x in res[i]:
            for y in res[i]:
                if len(y) < len(x) and x.find(y) >= 0:
                    break
            else:
                nres.add(x)
        res[i] = nres
    

REM_ALPH = 'abcdfghijklnpqrstuvxyz'
PATTERNS = [set() for _ in range(4)]
gen(list('meow'), 0, PATTERNS)
simplify(PATTERNS)

# Generate a case of length n over alphabet, where answer is ans,
# obtained by ans_pattern occuring at pos ans_pos, and no other
# pattern resulting in ans or lower appears anywhere.
def gen(n, ans, ans_pattern, ans_pos, alphabet):
    assert ans < 4
    sys.stderr.write('gen case len=%d ans=%d ans_pattern=%s ans_pos=%d alphabet=%s\n' % (n, ans, ans_pattern, ans_pos, alphabet))
    res = []
    while len(res) < n:
        res.append('.')
        match_pos = len(res)-1 - ans_pos
        if match_pos < 0 or match_pos >= len(ans_pattern):
            match_pos = -1
        while True:
            if match_pos < 0 or ans_pattern[match_pos] == '.':
                res[-1] = random.choice(alphabet)
            else:
                res[-1] = ans_pattern[match_pos]
            ok = True
            for smaller_ans in range(ans, -1, -1):
                for pattern in PATTERNS[smaller_ans]:
                    if len(pattern) > len(res): continue
                    should_have_pattern = (pattern == ans_pattern and len(res)-len(pattern) == ans_pos)
                    matches = True
                    for i in range(len(pattern)):
                        if pattern[i] not in [res[-len(pattern)+i], '.']:
                            matches = False
                    if matches != should_have_pattern:
                        ok = False
                        reason = pattern
                        break
                if not ok:
                    break
            if ok: break
            if match_pos >= 0 and ans_pattern[match_pos] != '.':
                sys.stderr.write('    failed at len %d (tail %s) because of %s, rewind 10 steps\n' % (len(res), ''.join(res[-15:]), reason))
                for i in range(min(10, len(res))): res.pop()
                break
    return ''.join(res)
            
def gen_random(n, alphabet):
    return ''.join(random.choice(alphabet) for _ in range(n))
    
def main():
    random.seed(42)

    save_case('meow', short_desc='meow')
    save_case('z', short_desc='z')
    save_case('o', short_desc='o')
    assert (MAX_LEN-1) % 3 == 0
    save_case('meo'*((MAX_LEN-1)/3) + 'w', short_desc='long_meomeomeow')
    
    interesting_patterns = len(PATTERNS[1]) + len(PATTERNS[2])
    
    for ((n_lo, n_hi), name) in zip([(10, 20), (100, 1000), (MAX_LEN, MAX_LEN)],
                                    ['small', 'medium', 'big']):
        interesting_seen = 0
        (first_match, last_match) = random.sample(range(interesting_patterns), 2)
        
        for ans in range(4):
            for pattern in PATTERNS[ans]:
                n = random.randint(n_lo, n_hi)
                ans_pos = random.randint(0, n-len(pattern))
                if ans in [1, 2]:
                    if interesting_seen == first_match: ans_pos = 0
                    elif interesting_seen == last_match: ans_pos = n-len(pattern)
                    interesting_seen += 1
                save_case(gen(n, ans, pattern, ans_pos,
                              'meow' + random.choice(REM_ALPH)),
                          short_desc='%s_%d' % (name, ans))
        n = random.randint(n_lo, n_hi)
        save_case(gen_random(n, REM_ALPH), short_desc='%s_%d' % (name, 4))
        n = random.randint(n_lo, n_hi)
        save_case(gen_random(n, 'meow' + REM_ALPH),
                  short_desc='%s_random' % name)

if __name__=='__main__':
    main()
