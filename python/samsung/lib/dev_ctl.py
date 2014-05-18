#!/usr/bin/env python
import dev_manip as dm

# if using toggle for perf_level you will get an error if trying to use binary values instead of normal or silent
def Toggle( device, value1, value2 ):
	""" Toggles state of device, should be used when you have a binary choice """
	currentVal = dm.ReadValue( device )
	if value1 in currentVal:
		return dm.WriteValue( device, value2 )
	else:
		return dm.WriteValue( device, value1 )

def On( device, onValue ):
	""" Turns device On, should be used where On is binary choice """
	return dm.WriteValue( device, onValue )

def Off( device, offValue ):
	""" Turns device off """
	return dm.WriteValue( device, offValue )

def Max( device, maxFile ):
	""" Changes device to maximum state, should be used where maximum is not binary """
	maxVal = dm.ReadValue( maxFile )
	return dm.WriteValue( device, maxVal )

def Up( device, maxFile ):
	""" Turns device up by 1 integer increment """
	maxVal = int( dm.ReadValue( maxFile ))
	currentVal = int( dm.ReadValue( device ))
	if maxVal == currentVal:
		return True
	else:
		return dm.WriteValue( device, currentVal + 1 )

def Down( device, minVal ):
	""" Turns device down by 1 integer increment """
	currentVal = int( dm.ReadValue( device ))
	minVal = int( minVal )
	if minVal == currentVal:
		return True
	else:
		return dm.WriteValue( device, currentVal - 1 )

#def Wifi():
	# on, off, default:toggle

#def Bluetooth():
	# on, off, default:toggle

#def Batt_Extender():
	# on, off, default:toggle

#def USB_Charge():
	# on, off, default:toggle

#def Performance():
	# normal, silent, default:toggle


#def KbdIllum():
	# max, off, up, down, default: do nothing

#def Monitor():
	# max, off, up, down, default: do nothing


# toggle, on, off, max, up, down
wlan = dm.wlan
bt = dm.bt
kbd_bright = dm.kbd_bright
kbd_maxBright = dm.kbd_maxBright
batt_extend = dm.batt_extend
perf_level = dm.perf_level
usb_charge = dm.usb_charge
mon_bright = dm.mon_bright
mon_maxBright = dm.mon_maxBright

# all of these worked perfect
#Toggle( bt, '1', '0' )
#Toggle( wlan, '1', '0' )
#Toggle( batt_extend, '1', '0' )
#Toggle( perf_level, 'silent', 'normal' )
#Toggle( usb_charge, '1', '0' )
#On( bt, '1' )
Off( bt, '0' )
On( wlan, '1' )
#Off ( wlan, '0' )
On( batt_extend, '1' )
#Off( batt_extend, '0' )
#On( perf_level, 'normal' )
Off( perf_level, 'silent' )
#On( usb_charge, '1' )
Off( usb_charge, '0' )

#Max( kbd_bright, kbd_maxBright )
#Off( kbd_bright, '0' )
#Max( mon_bright, mon_maxBright )
#Off( mon_bright, '0' )
#Up( mon_bright, mon_maxBright )
#Up( kbd_bright, kbd_maxBright )
#Down( mon_bright, '0' )
#Down( kbd_bright, '0' )
