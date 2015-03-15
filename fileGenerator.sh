#!/bin/bash

# This script generate cflow file which can be interpreted by dotgenerator program and the by dot

#################################################################
#								#
#	Usage: sh fileGenerator.sh C_FILE_PATH function_name	#
#								#
#################################################################


compilation=1
generatorLocalization="/home/henio/cflow_tests/dotGenerator.c"
outputFile="/home/henio/cflow_tests/dotGenerator"
cflowFile="/home/henio/cflow_tests/cflowFile"
outputImage="/home/henio/cflow_tests/output.png"
dotFile="/home/henio/cflow_tests/out.dot"

if [ $# != 2 ]; then
	echo "Uasge: sh fileGenerator.sh C_FILE_PATH function_name"
	exit 1
fi

if [ -f $1 ]; then
	echo -n "Creating CFLOW file... "
	cflow -o $cflowFile -m $2 $1
	
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
	echo -n "Creating .dot file... "
	$outputFile $cflowFile
else
	echo "$cflowFile or $outputFile doesn't exist"
	exit 1
fi

if [ -f $dotFile ]; then
	echo "OK"
	dot -Tpng $dotFile > $outputImage
else
	echo ".dot file doesn't exist - check dotGenerator"
fi

rm $cflowFile
rm $dotFile

echo "The end"
