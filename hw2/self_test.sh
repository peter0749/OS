#!/bin/bash
ARG1=100 ## NUMBER OF LOOPS
ARG2=100000 ## SIZE OF ARRAY
if [[ $# -ge 1 ]]; then
    ARG1=$1
fi
if [[ $# -ge 2 ]]; then
    ARG2=$2
fi
make &> /dev/null
AC=1
for ((i=1; i<$ARG1; ++i)); do
    seed=$RANDOM
    echo -n "Testing on check point $i ... "
    if ! diff -w -q <(./hw2 $seed $ARG2) <(./valid $seed $ARG2) &> /dev/null; then
        AC=0
        echo "wrong!"
        break
    fi
    echo "passed!"
done

if [[ $AC -eq 1 ]]; then
    echo "Accept"
else
    echo "Wrong"
fi
