#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

use_solution ng.cpp

compile gen_random.py
compile gen_triangle.py

MAXN=100000

samplegroup
sample 1
sample 2

group group1 5
tc 01.random gen_random n=$MAXN maxy=$MAXN
tc 02.random gen_random n=$MAXN maxy=$MAXN
tc 03.random gen_random n=$MAXN maxy=$MAXN
tc 04.random gen_random n=$MAXN maxy=10000
tc 05.random gen_random n=$MAXN maxy=1000
tc 06.random gen_random n=$MAXN maxy=100
tc 07.random gen_random n=$MAXN maxy=10
tc 08.random gen_random n=$MAXN maxy=1
tc 09.same_y gen_random n=$MAXN maxy=0
tc 10.oneways gen_random n=$MAXN maxy=$MAXN maxway=1
tc 11.oneways gen_random n=$MAXN maxy=10000 maxway=1
tc 12.oneways gen_random n=$MAXN maxy=10 maxway=1
tc 13.triangle gen_triangle n=$MAXN height=300
tc 14.triangle gen_triangle n=$MAXN height=1000
tc 15.small gen_random n=2 maxy=2
tc 16.small gen_random n=2 maxy=2
tc 17.small gen_random n=5 maxy=3
tc 18.small gen_triangle n=10 height=3
