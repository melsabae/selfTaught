#!/usr/bin/bash
cs121dir=/tmp/$(date +%b%d)
mkdir -p $cs121dir
cd $cs121dir
wget -r --accept '*.jpg' http://www.cs.uah.edu/~rcoleman/CS121/TodaysClass/TodaysClass.html
mv $cs121dir /media/sf_vboxshare/
