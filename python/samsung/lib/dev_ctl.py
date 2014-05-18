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

