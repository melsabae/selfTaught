import os

sysdev = '/sys/devices/'
samsung = sysdev +  "platform/samsung/"

# readstring is in the event multiple files come up with the same name, we can hopefully pull a file with the path to the correct device dir this way
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

# ethernet, screen light, mouse, vga out, audio all might be found for controlling

# these files normally exist in platform/samsung subdir
bright = FindFile( "brightness", samsung, "" )
maxbright = FindFile( "max_brightness", samsung )
blextend = FindFile( "battery_life_extender", samsung )
perf_level = FindFile( "performance_level", samsung )
usb_charge = FindFile( "usb_charge", samsung )

# these -4 indices cut the 'name' off the end, we were only looking for the right directory, both of these devices have a 'name' file in their dir, we wanted the state file
wlan = FindFile( "name", samsung, 'samsung-wlan' )[:-4] + "state"
kt = FindFile( "name", samsung, 'samsung-bluetooth' )[:-4] + "state"
