#!/bin/bash

BASEDIR=$(dirname $0)
count=$(find ./programs -maxdepth 1 -name "*.asm" | wc -l)

for ((z=1; z<=$count;z++))
do
    "$BASEDIR"/../res_6/njc --output "$BASEDIR"/prog"$z".asm "$BASEDIR"/prog"$z".nj
done