#!/bin/bash

# This script generate cflow file which can be interpreted by dotgenerator program and the by dot

#################################################
#						#
#	Usage: sh fileGenerator.sh C_FILE_PATH	#
#						#
#################################################


compilation=1
generatorLocalization="/home/henio/cflow_tests/dotGenerator.c"
outputFile="/home/henio/cflow_tests/dotGenerator"
cflowFile="/home/henio/cflow_tests/cflowFile"
outputImage="/home/henio/cflow_tests/output.png"


if [ $# != 1 ]; then
	echo "Uasge: sh fileGenerator.sh C_FILE_PATH"
	exit 1
fi

if [ -f $1 ]; then
	echo -n "Creating CFLOW file... "
	cflow -o $cflowFile $1
	
	if [ -f $cflowFile ]; then
		echo "OK"

	else
		echo "Err"
		exit 1
	fi 
else
	echo "$1 doesn't exist"
	exit 1
fi

if [ $compilation == 1 ]; then
	echo -n "Compilation... "
	gcc -Wall $generatorLocalization -o $outputFile
	
	if [ -f $outputFile ]; then
		echo "OK"
	else
		echo "Err"
		exit 1
	fi
fi
if [ -f $outputFile ] && [ -f $cflowFile ]; then
	$outputFile $cflowFile
else
	echo "$cflowFile or $outputFile doesn't exist"
	exit 1
fi

if [ -f text.dot ]; then
	dot -Tpng text.dot > $outputImage
else
	echo ".dot file doesn't exist - check dotGenerator"
fi

echo "The end"
