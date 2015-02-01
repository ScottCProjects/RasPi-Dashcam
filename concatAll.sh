#! /bin/bash

# arg1 = Prefix of output files
# arg2 = Total number of output files
# arg3 = File number last recorded over. Will be 0 bytes in size

prefix=$1 #Prefix of output files
numFiles=$2 #Total number of output files
#startNum=$3 #File number last recorded over. Will be 0 bytes in size

outFile="$prefix"All.h264
echo Output File: $outFile
cat test0.h264 > $outFile

# Figure out which file to start with
startNum=`find ./ -maxdepth 1 -size 0 | sort | head -1 | sed -r 's/.*[a-zA-Z]+([0-9]+).h264/\1/g'`

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
