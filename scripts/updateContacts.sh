<<<<<<< HEAD
# script that pulls in tracker's adt table file and pulls out contacts # since the database engine doesn't offer anything other than GUI, had to pull straight out of the file using strings
=======
# script that pulls in tracker's adt table file and pulls out contacts
# since the database engine doesn't offer anything other than GUI, had to pull straight out of the file using strings
>>>>>>> 37711b4b2146d0d3ae79c9137e3aec1f8d8ff707
# quick-n-dirty but the output has not failed _YET_

#!/bin/bash
# include stdsarcasm.h

# not normally what i would do but it cleans up some other parts and runs leaner
cd ~/contactwork

trk_serv=//rzpc
trk_dir_remote=$trk_serv/trk
fail_log=./faillog.txt

# fail message pulls straight from get operation, combines with an echo to put out smbclient exit code
<<<<<<< HEAD
	# runs faster than before when done like this
=======
>>>>>>> 37711b4b2146d0d3ae79c9137e3aec1f8d8ff707
fail_message=`smbclient -N $trk_dir_remote -c "cd CO0002; prompt; get INVUSER.ADT; exit;"; echo ": smbclient exit code $?"`

# magical all-encompassing error reporting
case $fail_message in
	*[Ff][Aa][Ii][Ll][Ee][Dd]*)
		echo {`date +%a\ %F\ %T`} operation failed with error: $fail_message >> $fail_log;
		exit 1;;
	*[Ee][Rr][Rr][Oo][Rr]*)
		echo {`date +%a\ %F\ %T`} operation failed with error: $fail_message >> $fail_log;
		exit 1;;
esac

# survived.
	# just in case
	unset fail_message fail_log trk_dir_remote trk_serv
contact_outfile=./contacts.csv
copy_file=/mnt/Share/contacts.csv
adt_file=./INVUSER.ADT

# blows away file with new copy, because laziness++
	# column headings, double quoted for consistency with later entries
<<<<<<< HEAD
=======
	# if in the event i use output in other applications
>>>>>>> 37711b4b2146d0d3ae79c9137e3aec1f8d8ff707
echo '"STOCK","SOURCE","CONTACT"' > $contact_outfile

	# it gets gnarly here
	# AKA: the actual work
# 1. we're using strings because there's no shell for the database engine we have to use
<<<<<<< HEAD
# 2. grep out stock numbers
# 3. a cut, since the database engine stores unused space as whitespace, this makes the next part simpler
# 4. grep away anything not having a purchase source and/or a contact
#    notice the | separating regexes
# 5. comma delimit && wrap each token in double quotes, then remove extra whitespace
#    because sometimes purchase source or contacts fields have commas in it, we wrap tokens in double quotes without having to try and remove said commas
	# database stores stock number as first 8 chars, purchase source as next 30, and contact field as final 30, this is where those magic numbers
	# come from
		# sometimes stores whitespace at the end of tokens, we can use field widths later on, or correct it in this script
#    then remove extra whitespace
# 6. sort
# 7. then dump output into a .csv file
strings $adt_file \
	| grep -P "^[a-lA-L][0-9]{3} .*" \
	| cut -c1-68 \
	| grep -vP "^[a-lA-L][0-9]{3} {3,4}[\w ]{1,30}$|^.{38}[^a-zA-Z]*$" \
	| sed -e 's_\(.\{8\}\)\(.\{30\}\)\(.*\)_"\1","\2","\3"_g' -e 's_\ \{2,\}__g' \
	| sort \
	>> $contact_outfile
=======
#     probably unsanitary
# 2. grep out all matching new stock numbers
# 3. a cut, since the database engine stores unused space as whitespace, this makes the next part simpler
# 4. grep away anything not having a purchase source and/or a contact
#    notice the \| separating regexes
# 5. comma delimit && wrap each token in double quotes, then remove extra whitespace
#    because sometimes purchase source or contacts fields have commas in it, we wrap tokens in double quotes to properly delimit them without having to try and remove said commas
#    then remove extra whitespace
# 6. sort then dump output into a .csv file
strings $adt_file \
	| grep -P ^[a-lA-L][0-9]\{3\}\ .* \
	| cut -c1-68 \
	| grep -vP ^[a-lA-L][0-9]\{3\}\ \{3,4\}[\w\ ]\{1,30\}$\|^.\{38\}[^a-zA-Z]*$ \
	| sed -e 's_\(.\{8\}\)\(.\{30\}\)\(.*\)_"\1","\2","\3"_g' -e 's_ \{2,\}__g' \
	| sort >> $contact_outfile
>>>>>>> 37711b4b2146d0d3ae79c9137e3aec1f8d8ff707

cp $contact_outfile $copy_file

# <srs> so people can't modify output file by accident </srs>
chmod 644 $copy_file

# just in case
unset trk_serv trk_dir_remote contact_outfile copy_file adt_file

exit 0
