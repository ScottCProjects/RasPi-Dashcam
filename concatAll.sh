#! /bin/bash

prefix=$1
numFiles=$2
startNum=$3

outFile="$prefix"All.h264

echo Output File: $outFile

cat START.h264 > $outFile

declare -i i
i=$startNum
((++i))

while [ $i -le $numFiles ]
do
	cat $prefix$i.h264 >> $outFile
	((++i))
done

i=1
while [ $i -lt $startNum ]
do
	cat $prefix$i.h264 >> $outFile
	((++i))
done
