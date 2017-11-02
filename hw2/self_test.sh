#!/bin/bash
if [[ $# -eq 0 ]]; then
    ARG1=10
else
    ARG1=$1
fi
make &> /dev/null
AC=1
for ((i=1; i<$ARG1; ++i)); do
    seed=$RANDOM
    sync
    if ! diff -w -q <(./hw2 $seed $i) <(./valid $seed $i); then
        rm -f a b
        AC=0
        break
    fi
    rm -f a b
done

if [[ $AC -eq 1 ]]; then
    echo "AC"
else
    echo "WA"
fi
