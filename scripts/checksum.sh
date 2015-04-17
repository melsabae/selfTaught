#!/bin/bash

if [ -e $1 ] && [ -f $1 ] && [ -s $1 ] && [ -r $1 ]
	then
		echo -e 'SHA1\t' $( sha1sum $1 | sed -e 's_\ .*__g' )
		echo -e 'SHA512\t' $( sha512sum $1 | sed -e 's_\ .*__g' )
		echo -e 'MD5\t' $( md5sum $1 | sed -e 's_\ .*__g' )
fi
