#!/usr/bin/env python
import dev_manip as dm

# would have preferred programmatic discovery
# cheesing it here, but maaaaaaaaan is it simpler

# monitor directory is important, there are 2 directories under backlight
# and if acpi is not chosen, we might get the other directory which controls
# the same hardware, which it's minimum value turns the screen off
# instead of fully dimming it out like i want
monitor = '/sys/class/backlight/acpi_video0/'
samsung = '/sys/devices/platform/samsung/'

# base class for all devices i have on my machine, including binary
class Device:
	def __init__( self, name, dirs, onVal, offVal, options ):
		self.name = name
		self.dirs = dirs
		self.onVal = onVal
		self.offVal = offVal
		self.options = options

		self.Path = self.DefinePath()

	def DefinePath( self ):
		return dm.FindFile( self.name, self.dirs, self.options )

	def Read( self ):
		return dm.ReadValue( self.Path )

	def Write( self, value ):
		if value == 'on':
			value = '1'
		elif value == 'off':
			value = '0'
		return dm.WriteValue( self.Path, value )

	def GetPath( self ):
		return self.Path

	def Off( self ):
		return self.Write( self.offVal )

	def On( self ):
		return self.Write( self.onVal )
	
	# not going to be used, and haven't figured it out anyway
	def Toggle( self ):
		pass

# for devices that do not have binary state
class RangeDevice( Device ):
	def RangeDefine( self, minVal, increment, maxValFile, decrement ):
		self.minVal = minVal
		self.increment = increment
		self.decrement = decrement
		self.maxVal = self.MaxVal( maxValFile )

	def MaxVal( self, _file ):
		readfile = dm.FindFile( _file, self.dirs, '' )
		with open ( readfile, 'r' ) as f:
			return f.readline()

	# override on value since on can be anything > OFF in range devices
	def On( self ):
		pass
				
	def Max( self ):
		return dm.WriteValue( self.Path, self.maxVal )

	def Up( self ):
		if int( self.Read() ) < int( self.maxVal ):
			return dm.WriteValue( self.Path,
				int ( self.Read() + int ( self.increment )))
		else:
			return True

	def Down( self ):
		if int( self.Read() ) > int ( self.minVal ):
			return dm.WriteValue( self.Path,
				int ( self.Read() -int (self.decrement )))
		else:
			return True

# binary devices
#perf = Device( 'performance_level', samsung, 'normal', 'silent', '' )
#perf.On()
#perf.Off()
#bt = Device( 'name', samsung, 1, 0, 'samsung-bluetooth' )
#bt.Path = bt.Path[:-4] + 'state'
#bt.On()
#bt.Off()
#wlan = Device( 'name', samsung, 1, 0, 'samsung-wlan' )
#wlan.Path = wlan.Path[:-4] + 'state'
#wlan.Off()
#wlan.On()
#usb = Device( 'usb_charge', samsung, 1, 0, '' )
#usb.On()
#usb.Off()
#batt = Device( 'battery_life_extender', samsung, 1, 0, '' )
#batt.Off()
#batt.On()

# range devices
#kbd_bright = RangeDevice( 'brightness', samsung, 8, 0, '' )
#kbd_bright.RangeDefine( '0', '1', 'max_brightness', '1' )
#mon_bright = RangeDevice( 'brightness', monitor, 100, 0, '' )
#mon_bright.RangeDefine( '0', '1', 'max_brightness', '1' )
