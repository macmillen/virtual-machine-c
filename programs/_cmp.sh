#!/bin/bash

BASEDIR=$(dirname $0)

for ((z=1; z<=99;z++))
do
    "$BASEDIR"/../res_7/njc --output "$BASEDIR"/prog"$z".asm "$BASEDIR"/prog"$z".nj
done