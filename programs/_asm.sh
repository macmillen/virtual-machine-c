#!/bin/bash

BASEDIR=$(dirname $0)
count=$(find ./programs -maxdepth 1 -name "*.asm" | wc -l)
for ((z=1; z<=$count;z++))
do
    "$BASEDIR"/../res_6/nja programs/prog"$z".asm programs/prog"$z".bin
done