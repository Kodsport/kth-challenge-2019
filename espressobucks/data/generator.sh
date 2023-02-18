#!/usr/bin/env bash

PPATH=$(realpath ..)
USE_ACM=1
. gen.sh

use_solution ng.cpp

compile gen_random.py

sample 1
sample 2

tc 01.random gen_random n=100 m=100 land=3000
tc 02.random gen_random n=100 m=100 land=4000
tc 03.random gen_random n=97 m=100 land=5000
tc 04.random gen_random n=100 m=93 land=7000
tc 05.random gen_random n=100 m=100 land=8000
tc 06.random gen_random n=100 m=100 land=9000
tc 07.no_water gen_random n=100 m=100 land=10000
tc 08.islands gen_random n=100 m=100 land=1000
tc 09.islands gen_random n=100 m=100 land=400
tc 10.islands gen_random n=100 m=100 land=30
tc 11.island gen_random n=100 m=100 land=1
tc 12.one_cell gen_random n=1 m=1 land=1
tc 13.random gen_random n=30 m=30 land=100
tc 14.long gen_random n=15 m=77 land=500
tc 15.long gen_random n=99 m=11 land=400
tc 16.long gen_random n=99 m=4 land=100
tc 17.long gen_random n=99 m=3 land=200
tc 18.long gen_random n=2 m=100 land=150
tc 19.long gen_random n=100 m=2 land=90
tc 20.line gen_random n=100 m=1 land=50
tc 21.line gen_random n=100 m=1 land=90
tc 22.line gen_random n=100 m=1 land=100
tc 23.line gen_random n=1 m=100 land=100
tc 24.line gen_random n=1 m=99 land=60
tc 25.line gen_random n=1 m=10 land=6
