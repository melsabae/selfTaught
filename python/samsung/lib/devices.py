#!/usr/bin/env python
import dev_manip as dm

# if using toggle for perf_level you will get an error if trying to use binary values instead of normal or silent
def Toggle( device, value1, value2 ):
	currentVal = dm.ReadValue( device )
	if value1 in currentVal:
		return dm.WriteValue( device, value2 )
	else:
		return dm.WriteValue( device, value1 )

def On( device, onValue ):
	return dm.WriteValue( device, onValue )

def Off( device, offValue ):
	return dm.WriteValue( device, offValue )

def Max( device, maxValue ):
	return dm.WriteValue( device, maxValue )

def Up( device, maxVal ):
	currentVal = dm.ReadValue( device )
	if maxVal in currentVal:
		return True
	else:
		return dm.WriteValue( device, ++currentVal )

def Down( device, currentVal, minVal ):
	currentVal = dm.ReadValue( device )
	if minVal in currentVal:
		return True
	else:
		return dm.WriteValue( device, --currentVal )

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
