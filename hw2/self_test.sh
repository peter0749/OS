#!/bin/bash
ARG1=1000 ## NUMBER OF LOOPS
ARG2=10000000 ## SIZE OF ARRAY
STEP=$((ARG2/ARG1))
echo "Step size: $STEP"
if [[ $# -ge 1 ]]; then
    ARG1=$1
fi
if [[ $# -ge 2 ]]; then
    ARG2=$2
fi
make &> /dev/null
AC=1

temp1=$(mktemp)
temp2=$(mktemp)

rm -f "log_hw2" "log_valid"
TIMEFORMAT=%R

for ((i=1; i<=$ARG1; ++i)); do
    seed=$RANDOM
    echo -n "Testing on check point $i ... "
    sync
    time (./hw2 $seed $((STEP*i)) > "$temp1") >> "log_hw2" 2>&1
    sync
    time (./valid $seed $((STEP*i)) > "$temp2") >> "log_valid" 2>&1
    sync
    if ! diff -w -q "$temp1" "$temp2" &> /dev/null; then
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
