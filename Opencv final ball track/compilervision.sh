#!/bin/sh

if [ $# -gt 0 ] ; then
	base=`basename $1 .cpp`
	echo "compiling $base"
	g++ -ggdb `pkg-config --cflags opencv` -o $base $base.cpp `pkg-config --libs opencv` -pthread ;
else
	printf "filenya mana brooo \n";

fi
