#!/bin/bash

BASEDIR=$(dirname $0)
count=$(find ./programs -maxdepth 1 -name "*.asm" | wc -l)
RED='\033[0;31m'
NC='\033[0m' # No Color

for ((z=1; z<="$count";z++))
do
    echo --- Test: "$z" ---
    "$BASEDIR"/../res_6/njvm programs/prog"$z".bin > tests/tst1_"$z".txt
    "$BASEDIR"/../njvm programs/prog"$z".bin > tests/tst2_"$z".txt
    diff=$(comm -3 "$BASEDIR"/../tests/tst1_"$z".txt "$BASEDIR"/../tests/tst2_"$z".txt)
    if [ "$diff" = "" ]; then
        hallo=$diff
    else
        echo -e $RED Test "$z" FAILED: "$diff" $NC
    fi
done