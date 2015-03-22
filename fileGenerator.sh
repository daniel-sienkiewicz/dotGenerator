#!/bin/bash

# This script generate cflow file which can be interpreted by dotgenerator program and the by dot

#################################################
#						#
#	Usage: sh fileGenerator.sh --help	#
#						#
#################################################

cflowFile="cflowFile"
outputImage="output.png"
dotFile="out.dot"

while test $# -gt 0; do
	case "$1" in
		-h|--help)
			echo "$package - attempt to capture frames"
			echo " "
			echo "$package [options] application [arguments]"
			echo " "
			echo "options:"
			echo "-h, --help              show brief help"
			echo "-c, --compile=FILE      compile dot Generator"
			exit 0
			;;
		-c)		
			echo -n "Compilation... "
			gcc -Wall $2
			if [ -f a.out ]; then
				echo "OK"
			else
				echo "Err"
				exit 1
			fi
			shift
			;;
		--compile*)
			echo -n "Compilation... "
			gcc -Wall $2
			if [ -f a.out ]; then
				echo "OK"
			else
				echo "Err"
				exit 1
			fi
			shift
			;;
		*)
			break
			;;
	esac
done

if [ $# = 0 ]; then
	echo "Uasge: sh fileGenerator.sh FLAGS"
	echo "See --help"
	exit 1
fi

echo -n "Creating CFLOW file... "
cflow -o $cflowFile -m $2 $1

if [ -f $cflowFile ]; then
	echo "OK"
else
	echo "Err"
	exit 1
fi

if [ ! -f a.out ]; then
	echo -n "Compilation..."
	gcc -Wall dotGenerator.c
	if [ -f a.out ]; then
		echo "OK"
	else
		echo "Err"
		exit 1
	fi
fi

echo -n "Creating .dot file... "
./a.out $cflowFile
if [ -f $cflowFile ];then
	echo "OK"
else
	echo "Err"
	exit 1
fi

dot -Tpng $dotFile > $outputImage

echo -n "Cleaning up... "
#rm $dotFile
#rm $cflowFile

if [ ! -f $dotFile ] && [ ! -f $cflowFile ]; then
	echo "OK"
else
	echo "Err"
fi

echo "The end"
