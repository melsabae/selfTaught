#!/bin/bash
# include stdsarcasm.h

DIR=/home/saba/contactwork
TRKSERV=//rzpc
FAIL=`smbclient -NL $TRKSERV | head -1`

# magical all-encompassing error reporting
case $FAIL in
	*[Ff]ailed*)
		echo `date` "with error:" $FAIL >> $DIR/faillog.txt;
		exit;;
	*[Ee]rror*)
		echo `date` "with error:" $FAIL >> $DIR/faillog.txt;
		exit;;
esac

# survived.
REMOTE=//rzpc/trk
OUTFILE=$DIR/contacts.csv
COPYFILE=/mnt/Share/contacts.csv
ADTFILE=$DIR/INVUSER.ADT

smbclient -N $REMOTE -c "cd CO0002; lcd $DIR; prompt; get INVUSER.ADT; exit;"

# blows away file with new copy, because laziness++
echo 'STOCK,SOURCE,CONTACT' > $OUTFILE

# it gets gnarly here
# AKA: the actual work
strings $ADTFILE | grep -P ^[a-lA-L][0-9]\{3\}\ .* | cut -c1-68 | grep -vP ^[a-lA-L][0-9]\{3\}\ \{3,4\}[\w\ ]\{1,30\}$ | grep -vP ^.\{38\}[^a-zA-Z]*$ | sed -e 's_\(.\{8\}\)\(.\{30\}\)\(.*\)_"\1","\2","\3"_g' -e 's_ \{2,\}__g' | sort >> $OUTFILE

cp $OUTFILE $COPYFILE

# <srs> so people can't modify output file by accident </srs>
chmod 644 $COPYFILE
exit 0
