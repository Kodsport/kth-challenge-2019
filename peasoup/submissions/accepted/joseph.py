#!/usr/bin/env python3
n = int(input())

favorite = "Anywhere is fine I guess"
for place in range(n):
    peasoup = False
    pancakes = False
    ki = int(input())
    name = input()
    for menu in range(ki):
        item = input()
        peasoup = peasoup or item == "pea soup"
        pancakes = pancakes or item == "pancakes"
    if peasoup and pancakes:
        favorite = name
        break

print(favorite)
