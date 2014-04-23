#! /bin/bash
## Scott Camarena
## 
## Dashcam
##   - Configuration Script
##============================================================

#Record loop
for i in {1..10}
do
	echo "i = " $i
	raspivid -w 640 -h 480 -fps 25 -t 10000 -o video25fps.$i.h264 
done
