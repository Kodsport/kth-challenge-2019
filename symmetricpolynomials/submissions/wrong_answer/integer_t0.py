#!/usr/bin/env python3
import sys

def binom(n, k):
    r = 1
    for i in range(k):
        r = r*(n-i)/(i+1)
    return r

def read_poly():
    _ = input()
    return list(reversed(list(map(int, input().split()))))


def trans(P, t0):
    R = []
    for i in range(len(P)):
        coeff = (0, 1)
        t0_pow = (1, 1)
        for k in range(i, len(P)):
            add = (binom(k, i)*P[k]*t0_pow[0], t0_pow[1])
            coeff = (coeff[0]*add[1] + add[0]*coeff[1], coeff[1]*add[1])
            t0_pow = (t0_pow[0]*t0[0], t0_pow[1]*t0[1])
        R.append(coeff)
    return R


def solve(X, Y):
    d = max(len(X), len(Y)) - 1
    X = X + [0]*(d+1-len(X))
    Y = Y + [0]*(d+1-len(Y))
    if d == 0:
        return (-Y[0], X[0], 0) if Y[0] != 0 or X[0] != 0 else (1, 0, 0)
    if d == 1:
        return (X[1], Y[1], 0)

    if d % 2:
        (C, S) = (-Y[d], X[d])
    else:
        (C, S) = (X[d], Y[d])

    (Xrot, Yrot) = list(zip(*[(C*x + S*y, -S*x + C*y) for (x, y) in zip(X, Y)]))

    # Ooops: code thinks t0 is integer
    if d % 2:
        t0 = (-Yrot[d-1]/(d*Yrot[d]), 1)
    else:
        t0 = (-Xrot[d-1]/(d*Xrot[d]), 1)

    Xtrans = trans(Xrot, t0)
    Ytrans = trans(Yrot, t0)

    for i in range(1, d, 2):
        if Xtrans[i][0]:
            return (0, 0, 0)
    for i in range(2, d, 2):
        if Ytrans[i][0]:
            return (0, 0, 0)

    const = Ytrans[0]
    return (S*const[1], -C*const[1], const[0])

def gcd(a, b):
    if a < 0: a = -a
    if b < 0: b = -b
    return gcd(b, a % b) if b else a

X = read_poly()
Y = read_poly()
(A, B, C) = solve(X, Y)
if A != 0 or B != 0 or C != 0:
    d = gcd(gcd(A, B), C)
    A /= d
    B /= d
    C /= d
print('%d %d %d' % (A, B, C))
