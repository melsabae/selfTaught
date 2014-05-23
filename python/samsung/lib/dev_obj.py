#!/usr/bin/env python
import dev_manip as dm
import dev_ctl as dc

sys_devices = '/sys/devices/'
samsung = sys_devices + 'platform/samsung/'

# base class for all devices i have on my machine
class Device:
	def __init__( self, name, dirs, onVal, offVal, options ):
		self.name = str( name )
		self.dirs = str( dirs )
		self.onVal = str( onVal )
		self.offVal = str( offVal )
		self.options = str( options )

		self.Path = str( self.GetPath() )

	def GetPath( self ):
		return dm.FindFile( self.name, self.dirs, self.options )

	def Read( self ):
		return dm.ReadValue( self.Path )

	def Write( self, value ):
		return dm.WriteValue( self.Path, value )

# devices with on or off modes only, not necessarily 0 or 1
class BinaryDevice( Device ):
	def On( self ):
		return dm.WriteValue( self.Path, self.onVal )

	def Off( self ):
		return dm.WriteValue( self.Path, self.offVal )

	def Toggle( self ):
		# lazy skip of type checking
		if self.name == 'performance_level':
			return

		if int( self.Read() ) == int( self.onVal ):
			return self.Off()
		else:
			return self.On()

# for devices that do not have binary state
class RangeDevice( Device ):
	def RangeSet( self, minVal, maxVal ):
		self.minVal = int( minVal )
		self.maxVal = int( maxVal )

	def Max( self ):
		return dm.WriteValue( self.Path, self.maxVal )

	def Up( self ):
		if self.Read() < self.maxVal:
			return dm.WriteValue( self.Path, int ( self.Read() + 1 ))
		else:
			return True

	def Down( self ):
		if self.Read() > self.minVal:
			return dm.WriteValue( self.Path, int ( self.Read() -1 ))
		else:
			return True

#perf = BinaryDevice( 'performance_level', samsung, 'normal', 'silent', '' )
#perf.On()
#perf.Off()
#perf.Toggle()
#bt = BinaryDevice( 'name', samsung, 1, 0, 'samsung-bluetooth' )
#bt.Path = bt.Path[:-4] + 'state'
#bt.On()
#bt.Off()
#bt.Toggle()
wlan = BinaryDevice( 'name', samsung, 1, 0, 'samsung-wlan' )
kbd_bright = RangeDevice( 'brightness', samsung, 8, 0, '' )

