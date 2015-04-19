#!/usr/bin/env python2.7
import os

dupes = open("summed", 'r')
dupes2 = open("summed",'r')

# file where duplicates will be recorded with hashes and filenames
work = open("worked_hashes", "w")

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
