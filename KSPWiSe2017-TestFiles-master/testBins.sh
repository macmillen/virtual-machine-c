#!/bin/bash
vm=../njvm
$vm
folder=Version8/
$vm $folder/keek
$vm $folder blub.abc
for f in $folder*.bin
do
	echo "<S> to skip $f, <Any> to execute $f";
	read skip;
	if [ "$skip" != "S" ] ; then
	echo "Testing with $f";
	echo "";
	$vm $f;
	fi
	done
