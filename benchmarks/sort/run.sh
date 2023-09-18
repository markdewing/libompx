#!/bin/bash

EXE=./a.out
${EXE} --only-print-header
for n in 1000 2000 5000 10000 20000 50000 100000 200000 500000 1000000 2000000
do
    ${EXE} -n $n --no-header -l 100
done
