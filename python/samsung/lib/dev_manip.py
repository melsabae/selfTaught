import os

sysdev = '/sys/devices/'
samsung = sysdev + 'platform/samsung/'

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
def FindFileStruct( filename, searchpath, dirname ):
	for root, subdirs, files in os.walk( searchpath ):
		if dirname in subdirs:
			return os.path.join( root, dirname, filename )

# this will blow away the file's current contents, as we are currently wanting to do for hardware control
# we use string here in the  write to make python happy, in the end the linux kernel will read it out of the file as the type it needs
def WriteValue( device, value ):
	value2 = str( value )
	with open( device, 'w' ) as _file:
		return _file.write( value2 )

def ReadValue( device ):
	with open( device, 'r' ) as _file:
		return _file.readline()

# these files exist under /sys/devices/platform/samsung on my machine

#the [:-4] removes the name file, the file we are interested in the contents of, not the actual file itself(both radios employ the same filenames), replacing it with state, the name of the file that controls power to these radios
bt = FindFile( "name", samsung, "samsung-bluetooth" )
bt = bt[:-4] + "state"
wlan = FindFile( "name", samsung, "samsung-wlan" )
wlan = wlan[:-4] + "state"

kbd_bright = FindFile( "brightness", samsung )
kbd_maxBright = FindFile( "max_brightness", samsung )
batt_extend = FindFile( "battery_life_extender", samsung )
perf_level = FindFile( "performance_level", samsung )
usb_charge = FindFile("usb_charge", samsung )

# these 2 files exist above platform/samsung so we're using a new path to search for them
# there is a second directory on my machine that contains an interface to manipulate backlight of the screen, but the legal values can reach as low as 0, turning off the screen entirely and you'd need to write in a value of up to 4650 to turn it back on, hence the acpi_video0 that explicitly states which one i want
# as well as a radio LED that exists in this structure, but we cannot control that directly from file IO, so acpi_video0 is necessity
mon_bright = FindFileStruct( "brightness", sysdev, "acpi_video0" )
mon_maxBright = FindFileStruct( "max_brightness", sysdev, "acpi_video0" )

# can we find the ethernet, mouse, vga out, and audio functions?

