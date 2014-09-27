import os

# we use readstring in the event multiple file paths match the name in the searchpath, we can return which one we like based on that file's expected contents if we pass it in as readstring, else readstring is default an empty literal
def FindFile( filename, searchpath, readstring = "" ):
	for root, subdirs, files in os.walk( searchpath ):
		for _file in files:
			# if we have no readstring, just get filepath
			if filename == _file and readstring == "":
				return os.path.join( root, _file )
			# if we have a readstring, check contents and return path if correct
			elif filename == _file and readstring != "":
				tmp = os.path.join( root, _file )
				with open( tmp, 'r' ) as f:
					if readstring in f.readline():
						return tmp
			# test this else clause extensively
			# maybe popup a dialog box saying what couln't be found, instead of returning None and then checking for None later
			#else:
				#return None

# sometimes the values of FindFile's return file will match multiple files, so we want to match a parent directory's name instead
# currently unused
def FindFileStruct( filename, searchpath, dirname ):
	for root, subdirs, files in os.walk( searchpath ):
		if dirname in subdirs:
			return os.path.join( root, dirname, filename )

# this will blow away the file's current contents, as we are currently wanting to do for hardware control, instead of appending
# we use string here in the  write to make python happy, in the end the linux kernel will read it out of the file as the type it needs
# rstrip just removes newlines as it is not necessary
def WriteValue( device, value ):
	with open( device, 'w' ) as _file:
		return _file.write( str( value ))

# simply lifts value out of the device file and returns as string
def ReadValue( device ):
	with open( device, 'r' ) as _file:
		return str( _file.readline().rstrip( '\n' ))

