#!/usr/bin/bash
cs307dir=/tmp/$(date +%b%d)
mkdir -p $cs307dir
cd $cs307dir
wget -r --accept '*.jpg' http://146.229.232.15/~rcoleman/CS307/TodaysClass/TodaysClass.html
#http://www.cs.uah.edu/~rcoleman/CS307/TodaysClass/TodaysClass.html
mv $cs307dir /media/sf_vboxshare/
