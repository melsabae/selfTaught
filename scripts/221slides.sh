#!/usr/bin/bash
cs121dir=/tmp/$(date +%b%d)
mkdir -p $cs121dir
cd $cs121dir
wget -r --accept '*.jpg' http://146.229.232.15/~rcoleman/CS221/TodaysClass/TodaysClass.html
#http://www.cs.uah.edu/~rcoleman/CS221/TodaysClass/TodaysClass.html
mv $cs121dir /media/sf_vboxshare/
