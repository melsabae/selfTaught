#!/bin/bash

cd ~/contactwork/

TRKSERV=//rzpc
REMOTE=//rzpc/trk
FAIL=`smbclient -NL $TRKSERV | head -1`

case $FAIL in
	*failed*) echo `date` "with error:"  $FAIL >> ~/contactwork/faillog.txt; exit;;
esac

smbclient -N $REMOTE -c "cd CO0002; prompt; get INVUSER.ADT; exit;"

echo 'STOCK,SOURCE,CONTACT' > ~/contactwork/contacts.csv
strings ~/contactwork/INVUSER.ADT | grep -P ^[a-lA-L][0-9]\{3\}\ .* | cut -c1-68 | grep -vP ^[a-lA-L][0-9]\{3\}\ \{3,4\}[\w\ ]\{1,30\}$ | grep -vP ^.\{38\}[^a-zA-Z]*$ | sed -e 's_\(.\{8\}\)\(.\{30\}\)\(.*\)_"\1","\2","\3"_g' -e 's_ \{2,\}__g' | sort >> ~/contactwork/contacts.csv
cp ~/contactwork/contacts.csv /mnt/Share/contacts.csv
chmod 644 /mnt/Share/contacts.csv
exit 0
