#!/bin/bash

TRKSERV=//rzpc
REMOTE=//rzpc/trk
FAIL=`smbclient -NL $TRKSERV | head -1`
DIR=/home/saba/contactwork
OUTFILE=$DIR/contacts.csv
COPYFILE=/mnt/Share/contacts.csv
ADTFILE=$DIR/INVUSER.ADT

case $FAIL in
	*failed*) echo `date` "with error:"  $FAIL >> ~/contactwork/faillog.txt; exit;;
esac

rm $DIR/INVUSER.ADT

smbclient -N $REMOTE -c "cd CO0002; lcd $DIR; prompt; get INVUSER.ADT; exit;"

echo 'STOCK,SOURCE,CONTACT' > $OUTFILE
strings $ADTFILE | grep -P ^[a-lA-L][0-9]\{3\}\ .* | cut -c1-68 | grep -vP ^[a-lA-L][0-9]\{3\}\ \{3,4\}[\w\ ]\{1,30\}$ | grep -vP ^.\{38\}[^a-zA-Z]*$ | sed -e 's_\(.\{8\}\)\(.\{30\}\)\(.*\)_"\1","\2","\3"_g' -e 's_ \{2,\}__g' | sort >> $OUTFILE
cp $OUTFILE $COPYFILE
chmod 644 $COPYFILE
exit 0
