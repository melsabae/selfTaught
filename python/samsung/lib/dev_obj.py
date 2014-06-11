#!/usr/bin/env python
import dev_manip as dm

# monitor directory is important, there are 2 directories under backlight
# and if acpi is not chosen, we might get the other directory which controls
# the same hardware, which it's minimum value turns the screen off
# instead of fully dimming it out like i want
monitor = '/sys/class/backlight/acpi_video0/'
samsung = '/sys/devices/platform/samsung/'

# base class for all devices i have on my machine, including binary
# name = filename to be found on synthetic filesystem
# replace = filename to be used on synthetic filesystem, used when multiple files will exist with the same 'name' under different directories
# dirs = toplevel directory to start search underneath
# onval = value for 'on'; not maximum value
# offval = value for 'off'; used as minimum value
# options = string to read from firstline of replace filename when searching through several files with same 'name'

# all variables will be strings when written or returned from read
# cast as appropriate?
class Device:
	def __init__( self, name, replace, dirs, onVal, offVal, options ):
		self.name = name
		self.replace = replace
		self.dirs = dirs
		self.onVal = onVal
		self.offVal = offVal
		self.options = options

		self.Path = self.DefinePath()

	def DefinePath( self ):
		tmp = dm.FindFile( self.name, self.dirs, self.options )
		if self.replace == '':
			return tmp
		else:
			return tmp.replace( self.name, self.replace )

	def Read( self ):
		return dm.ReadValue( self.Path ) 
	
	def Write( self, value ):
		# be wary of this if you change case, or more values become apparent for devices
		if value == 'on':
			value = '1'
		elif value == 'off':
			value = '0'
		return dm.WriteValue( self.Path, value )

	def Off( self ):
		return self.Write( self.offVal )

	def On( self ):
		return self.Write( self.onVal )
	
# for devices that do not have binary state
class RangeDevice( Device ):
	def SetBounds( self, increment, maxValFile, decrement ):
		self.increment = increment
		self.decrement = decrement
		self.maxVal = self.SetMax( maxValFile )

	def SetMax( self, _file ):
		readfile = dm.FindFile( _file, self.dirs, '' )
		with open ( readfile, 'r' ) as f:
			return f.readline().rstrip( '\n' )

	# override on value since on can be anything > OFF in range devices
	def On( self ):
		pass
				
	def Max( self ):
		return self.Write( self.maxVal )

	def Up( self ):
		if int( self.Read() ) < int( self.maxVal ):
			return self.Write( int ( self.Read() +
				int ( self.increment )))
		else:
			return True

	def Down( self ):
		if int( self.Read() ) > int ( self.offVal ):
			return self.Write( int ( self.Read() -
				int (self.decrement )))
		else:
			return True

