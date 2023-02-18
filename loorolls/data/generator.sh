#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

use_solution ng.cpp

compile gen.py

samplegroup
sample 1
sample 2

MAXL=10000000000

group group1 5
tc 01.random gen rand=1 maxl=$MAXL
tc 02.random gen rand=1 maxl=$MAXL
tc 03.random gen rand=1 maxl=$MAXL
tc 04.random gen rand=1 maxl=$MAXL
tc 05.random gen rand=1 maxl=$MAXL
tc 06.random gen rand=1 maxl=$MAXL
tc 07.random gen rand=1 maxl=$MAXL
tc 08.biganswer gen L=8550081721 N=8550081720
tc 09.biganswer gen L=8589933005 N=8589933004
tc 10.biganswer gen L=8688899522 N=8688899475
tc 11.N_equals_L gen L=$MAXL N=$MAXL
tc 12.N_divides_L gen L=10000000000 N=100000
tc 13.N_divides_L gen L=10000000000 N=1
tc 14.N_equals_L gen L=1 N=1
tc 15.small gen L=997153 N=997136
tc 16.small gen L=4621 N=66
