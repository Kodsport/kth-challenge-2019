import os
import random
import sys

MAX_DIM = 300

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), 'secret')

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '.' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(X, Y, short_desc=None, long_desc=None):
    while len(X) > 1 and X[-1] == 0: X = X[:-1]
    while len(Y) > 1 and Y[-1] == 0: Y = Y[:-1]
    sys.stderr.write('save_case degrees %d %d shortdesc %s\n' % (len(X)-1, len(Y)-1, short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%d\n' % (len(X)-1))
    f.write('%s\n' % (' '.join(map(str, reversed(X)))))
    f.write('%d\n' % (len(Y)-1))
    f.write('%s\n' % (' '.join(map(str, reversed(Y)))))
    f.close()


MAX_COEFF = 1000
MAX_DEG = 10

def random_poly(d):
    if d == 0:
        return [random.randint(-MAX_COEFF, MAX_COEFF)]
    return [random.randint(-MAX_COEFF, MAX_COEFF) for _ in range(d)] + [random.randint(1, MAX_COEFF)*random.choice([-1,1])]

# Random case, boring
def gen_random(d1, d2):
    X = random_poly(d1)
    Y = random_poly(d2)
    save_case(X, Y, short_desc='random_n%d_m%d' % (d1, d2))

def binom(n, k):
    r = 1
    for i in range(min(k, n-k)):
        r = r*(n-i)/(i+1)
    return r

def gcd(a, b):
    if a < 0: a = -a
    if b < 0: b = -b
    return gcd(b, a % b) if b else a

def lcm(a, b):
    return a*b/gcd(a, b)

def apply_trans(x, y, C, S, t0_num, t0_den):
    xr = [0]*len(x)
    yr = [0]*len(x)
    div = [0]*len(x)
    d = len(x)-1
    scale = 1
    for i in range(len(x)):
        div[i] = t0_den**(d-i)
        for k in range(i, len(x)):
            fac = binom(k, i) * t0_num**(k-i) * t0_den**(d-k)
            xr[i] = xr[i] + (C*x[k] + S*y[k]) * fac
            yr[i] = yr[i] + (-S*x[k] + C*y[k]) * fac
        scale = lcm(scale, div[i]/gcd(div[i], xr[i]))
        scale = lcm(scale, div[i]/gcd(div[i], yr[i]))
    for i in range(len(x)):
        assert xr[i]*scale % div[i] == 0
        assert yr[i]*scale % div[i] == 0
    return ([xr[i]*scale/div[i] for i in range(len(x))],
            [yr[i]*scale/div[i] for i in range(len(y))])

def check_trans(x, y, C, S, t0_num, t0_den):
    (xr, yr) = apply_trans(x, y, C, S, t0_num, t0_den)
    for i in range(len(x)):
        if abs(xr[i]) > MAX_COEFF:
            return False
        if abs(yr[i]) > MAX_COEFF:
            return False
    return True

# Random case that actually has a solution
def gen_random_symmetric(d, min_t0_den = 1):
    for _ in range(1000):
        t0_num = random.randint(-10, 10)
        t0_den = random.randint(1, 10)
        g = gcd(t0_num, t0_den)
        t0_num /= g
        t0_den /= g

        if t0_den < min_t0_den: continue

#        print 'try t0 = %d/%d' % (t0_num, t0_den)
        for _ in range(100):
            C = random.randint(-100, 100)
            S = random.randint(-100, 100)
            if C == 0 and S == 0: continue
            g = gcd(C, S)
            C /= g
            S /= g
            assert C or S

#            print '  try C = %d S = %d' % (C, S)

            x = [0]*(d+1)
            y = [0]*(d+1)
            if d % 2:
                x[d] = random.choice([-1,1])
            else:
                y[d] = random.choice([-1,1])

            if check_trans(x, y, C, S, t0_num, t0_den):
                for _ in range(10000):
                    i = random.randint(0, d)
                    delta = random.choice([-1, 1])
                    if i == d and x[d] + y[d] + delta == 0:
                        continue
                    if i == 0:
                        p = random.choice([x, y])
                    elif i % 2:
                        p = x
                    else:
                        p = y
                    p[i] += delta
                    if not check_trans(x, y, C, S, t0_num, t0_den):
                        p[i] -= delta
                print 'final: pre-rot and shift x %s y %s' % (x, y)
                (X, Y) = apply_trans(x, y, C, S, t0_num, t0_den)
                save_case(X, Y, short_desc='random_symmetric',
                          long_desc='Degree %d, normal of line is (%d, %d), t0 = %d/%d\n' % (d, C, -S, t0_num, t0_den))
                return


# Random case which is impossible but near-miss
# Figure out way to generate, is it possible?
def gen_random_nearmiss(d):
    pass

def main():
    random.seed(42)

    gen_random(0, 0)
    gen_random(1, 1)
    gen_random(1, 2)
    gen_random(2, 1)
    gen_random(2, 2)
    gen_random(2, 2)
    gen_random(2, 2)
    gen_random(3, 3)
    gen_random(3, 0)
    gen_random(0, 3)
    gen_random(4, 0)
    gen_random(0, 10)
    gen_random(10, 10)

    save_case([0], [0], short_desc='zeros')

    for d in range(3, MAX_DEG+1):
        for lb in range(1, 10):
            gen_random_symmetric(d, min_t0_den=lb)

if __name__=='__main__':
    main()
