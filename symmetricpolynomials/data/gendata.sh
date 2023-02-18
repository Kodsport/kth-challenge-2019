#!/bin/bash

#python gendata.py

for f in secret/*in; do
    python ../submissions/accepted/per_gcd.py < $f > ${f%.in}.ans
done
