#!/bin/bash

BASEDIR=$(dirname $0)

for ((z=1; z<=17;z++))
do
    "$BASEDIR"/../res_6/njc --output "$BASEDIR"/prog"$z".asm "$BASEDIR"/prog"$z".nj
done