#!/bin/bash

BASEDIR=$(dirname $0)

for ((z=1; z<=16;z++))
do
    "$BASEDIR"/../res_5/nja programs/prog"$z".asm programs/prog"$z".bin
done