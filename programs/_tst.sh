#!/bin/bash

BASEDIR=$(dirname $0)

for ((z=1; z<=17;z++))
do
    echo --- Test: "$z" ---
    "$BASEDIR"/../res_6/njvm programs/prog"$z".bin > tests/tst1_"$z".txt
    "$BASEDIR"/../njvm programs/prog"$z".bin > tests/tst2_"$z".txt
    diff=$(comm -3 "$BASEDIR"/../tests/tst1_"$z".txt "$BASEDIR"/../tests/tst2_"$z".txt)
    if [ "$diff" = "" ]; then
        hallo=$diff
    else
        echo Test "$z" FAILED
    fi
done