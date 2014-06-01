import os

# we use readstring in the event multiple file paths match the name in the searchpath, we can return which one we like based on that file's expected contents if we pass it in as readstring
def FindFile( filename, searchpath, readstring = "" ):
	for root, subdirs, files in os.walk( searchpath ):
		for file in files:
			if filename == file and readstring == "":
				return os.path.join( root, file )
			elif filename == file and readstring != "":
				tmp = os.path.join( root, file )
				with open( tmp, 'r' ) as f:
					if readstring in f.readline():
						return tmp

# sometimes the values of FindFile's return file will match, so we want to match a parent directory's name instead
# currently unused
def FindFileStruct( filename, searchpath, dirname ):
	for root, subdirs, files in os.walk( searchpath ):
		if dirname in subdirs:
			return os.path.join( root, dirname, filename )

# this will blow away the file's current contents, as we are currently wanting to do for hardware control
# we use string here in the  write to make python happy, in the end the linux kernel will read it out of the file as the type it needs
def WriteValue( device, value ):
	with open( device, 'w' ) as _file:
		return _file.write( str ( value ))

def ReadValue( device ):
	with open( device, 'r' ) as _file:
		return str( _file.readline() )

