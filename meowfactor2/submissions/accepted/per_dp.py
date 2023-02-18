#!/usr/bin/env python3
P = 'meow'
S = input()
n = len(S)
opt = [i % 5 for i in range(5*(n+1))]
ans = 4
for i in range(n):
    for j in range(4):
        opt[5*(i+1)+j+1] = min(opt[5*i+j+1] + 1, # del
                               opt[5*(i+1)+j] + 1, # ins
                               opt[5*i+j] + (S[i] != P[j])) # sub
        if i > 0 and j > 0 and S[i] == P[j-1] and S[i-1] == P[j]: # swap
            opt[5*(i+1)+j+1] = min(opt[5*(i+1)+j+1], 1 + opt[5*(i-1)+j-1])
    ans = min(ans, opt[5*(i+1)+4])
print(ans)
