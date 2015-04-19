#!/usr/bin/env python2.7
import os

<<<<<<< HEAD
dupes = open("summed", 'r')
dupes2 = open("summed",'r')

# file where duplicates will be recorded with hashes and filenames
work = open("worked_hashes", "w")
=======
dupes = open("hashed", 'r')
dupes2 = open("hashed",'r')

# file where duplicates will be recorded with hashes and filenames
work = open("matched_hashes", "w")
>>>>>>> bd292a3b0039aeafae555716848d5e0a6854eddd

# increment, otherwise it would check the same line against itself
dupes2.readline()

while True:
    line = dupes.readline()
    line2= dupes2.readline()

    if not line2:
        break

    # first 32 chars per line is md5sum
    if line[0:32] == line2[0:32]:
        work.write(line)
        work.write(line2)
        work.write("\n")

dupes.close()
dupes2.close()
work.close()
