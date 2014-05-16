#!/usr/bin/env python
import os

# should code logic of these scripts into python
# instead of relying on external files
# then replace ExecScript with a new function that runs direct
# will need to do effective-UID checks for control
bt_ctl = "bt_ctl.sh"
wifi_ctl = "wifi_ctl.sh"
perf_level = "perf_level.sh"
kbd_illum = "kbd_illum.sh"
script_dir = "scripts/"

def GetPath( _file ):
	""" Returns absolute path to script file """
	return os.path.abspath( script_dir + _file )

# only runs if file can be found, and then if it is executable per OS
# _option's default value is empty
def ExecScript( _file, _option="" ):
	""" Runs script file with options """
	if ( os.path.exists( _file ) and os.access( _file, os.X_OK )):
		return os.system( "sudo " + _file + " " + _option )

