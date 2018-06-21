#!/bin/bash

BASEDIR=$(dirname $0)

for ((z=1; z<=17;z++))
do
    "$BASEDIR"/../res_6/nja programs/prog"$z".asm programs/prog"$z".bin
done