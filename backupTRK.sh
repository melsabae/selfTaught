#!/bin/sh

MM=`date +%m`
MONTH=`date +%B`
DD=`date +%d`
DAY=`date +%A`
YYYY=`date +%Y`
BKDIR=/mnt/TRKBackups
ARCHDIR=$BKDIR/$YYYY/$MONTH/$DD\_$DAY\_rzpi
FRESHZIP=$BKDIR/BACKUP.ZIP
FRESHINI=$BKDIR/COMPANY.INI

FAIL=`smbclient -NL rzpc | head -1`
FAILDIR=$BKDIR/$YYYY/$MONTH/$DD\_$DAY\_DidNotRun\_rzpi

FIND=12/15/2012
REPLACE=$MM/$DD/$YYYY
BKCOFILE=/home/backups/COMPANY.INI[BACKUP]
COFILE=$ARCHDIR/COMPANY.INI

TMP=$BKDIR/.temp/CO0002
REMOTE=//rzpc/TRK

BKZIP=$ARCHDIR/BACKUP.ZIP

rm -f $TMP/*

case $FAIL in
	*failed*) mkdir $FAILDIR; rm -f $TMP/*; exit ;;
esac

rm $FRESHZIP $FRESHINI

smbclient -N $REMOTE -c "cd CO0002; lcd $TMP; prompt; mget *; exit;"

sleep 2
mkdir -p $ARCHDIR

sed -e s_$FIND\_$REPLACE\_g $BKCOFILE > $COFILE

7z a -mx9 -tzip $BKZIP $TMP/*
cp $BKZIP $FRESHZIP
cp $COFILE $FRESHINI

rm -f $TMP/*

exit
