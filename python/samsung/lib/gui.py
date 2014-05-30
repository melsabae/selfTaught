import Tkinter as tk
import tkMessageBox
import dev_obj as doj

class form( tk.Tk ):
	def __init__( self, parent ):
		tk.Tk.__init__( self, parent )
		parent = parent
		self.initialize()

	def initialize( self ):
		self.grid()
		self.title( 'Samsung Series9 Fn Control' )

		# brings device file paths into UI from doj

		# name, replacename, path, on value, off value, readstring
		perf_dev = doj.Device( 'performance_level', '',
				doj.samsung, 'normal', 'silent', '' )
		batt_dev = doj.Device( 'battery_life_extender', '',
				doj.samsung, '1', '0', '' )
		usb_dev = doj.Device( 'usb_charge', '',
				doj.samsung, '1', '0', '' )
		wifi_dev = doj.Device( 'name', 'state',
				doj.samsung, '1', '0', 'samsung-wlan' )
		bt_dev = doj.Device( 'name', 'state',
				doj.samsung, '1', '0', 'samsung-bluetooth' )

		# name, replace, path, on value, off value, options
		kbd_dev = doj.RangeDevice( 'brightness', '',
				doj.samsung, '8', '0', '' )
		mon_dev = doj.RangeDevice( 'brightness', '',
				doj.monitor, '100', '0', '' )

		kbd_dev.RangeDefine( '0', '1', 'max_brightness', '1' )
		mon_dev.RangeDefine( '0', '1', 'max_brightness', '1' )

		# contains all legal options for all hardware referenced
			# on my machine
		# not all hardware will use the entire list
		controlOpts = ( 'on', 'off', 'max',
				'up', 'down', 'silent', 'normal' )

		# default options to show on option menus
		# also contains variables to reference upon controls
		perf = tk.StringVar()
		wifi = tk.StringVar()
		bt = tk.StringVar()
		batt = tk.StringVar()
		usb = tk.StringVar()
		mon = tk.StringVar()
		kbd_bar_val = tk.StringVar()
		mon_bar_val = tk.StringVar()
		perf.set( controlOpts[ 5 ])
		wifi.set( controlOpts[ 0 ])
		bt.set( controlOpts[ 1 ])
		batt.set( controlOpts[ 0 ])
		usb.set( controlOpts[ 1 ])
		mon.set( controlOpts[ 1 ])
		kbd_bar_val.set( '0' )
		mon_bar_val.set( '0' )

		perfOpts = tk.OptionMenu( self, perf, *controlOpts[ 5:7 ])
		perfOpts.grid( column = 1, row = 0, sticky = tk.W + tk.E )
		# lambda keeps Tkinter from executing on instantiation
		perfBut = tk.Button( self, text = "Performance Level",
				command = lambda:
				perf_dev.Write( perf.get() ))
		perfBut.grid( column = 0, row = 0, sticky = tk.W + tk.E )

		wifiOpts = tk.OptionMenu( self, wifi, *controlOpts[ :2 ])
		wifiOpts.grid( column = 1, row = 1, sticky = tk.W + tk.E )
		wifiBut = tk.Button( self, text = "Wi-Fi Control", 
				command = lambda:
				wifi_dev.Write( wifi.get() ))
		wifiBut.grid( column = 0, row = 1, sticky = tk.W + tk.E )

		btOpts = tk.OptionMenu( self, bt, *controlOpts[ :2 ])
		btOpts.grid( column = 1, row = 2, sticky = tk.W + tk.E )
		btBut = tk.Button( self, text = "Bluetooth Control",
				command = lambda:
				bt_dev.Write( bt.get() ))
		btBut.grid( column = 0, row = 2, sticky = tk.W + tk.E )

		battOpts = tk.OptionMenu( self, batt, *controlOpts[ :2 ])
		battOpts.grid( column = 1, row = 3, sticky = tk.W + tk.E )
		battBut = tk.Button( self, text = "Battery Life Extender",
				command = lambda:
				batt_dev.Write( batt.get() ))
		battBut.grid( column = 0, row = 3, sticky = tk.W + tk.E )

		usbOpts = tk.OptionMenu( self, usb, *controlOpts[ :2 ])
		usbOpts.grid( column = 1, row = 4, sticky = tk.W + tk.E )
		usbBut = tk.Button( self, text = "USB Charging While Off",
				command = lambda:
				usb_dev.Write( usb.get() ))
		usbBut.grid( column = 0, row = 4, sticky = tk.W + tk.E )

		kbdBut = tk.Button( self, text = "Keyboard Backlight" )
		kbdBut.grid( column = 0, row = 5, sticky = tk.W + tk.E )

		# runs function on instantiation, this is NONO
		kbd_bar = tk.Scale( self,
				from_ = 0,
				to = kbd_dev.maxVal,
				resolution = kbd_dev.increment,
				orient = tk.HORIZONTAL,
				tickinterval = 4,
				variable = kbd_bar_val,
				# val is what is passed by scale's command
				command = lambda val:
					kbd_dev.Write( val ))

		kbd_bar.grid( column = 1,
				row = 5,
				sticky = tk.W + tk.E
				)

		monBut = tk.Button( self, text = "Monitor Brightness" )
		monBut.grid( column = 0, row = 6, sticky = tk.W + tk.E )

		# runs function on instantiation, this is NONO
		mon_bar = tk.Scale( self,
				from_ = 0,
				to = mon_dev.maxVal,
				resolution = mon_dev.increment,
				orient = tk.HORIZONTAL,
				tickinterval = 50,
				variable = mon_bar_val,
				command = lambda val:
					mon_dev.Write( val ))

		mon_bar.grid( column = 1,
				row = 6,
				sticky = tk.W + tk.E
				)

		quitBut = tk.Button( self, text = "Quit", command = quit )
		quitBut.grid( column = 0, row = 7, sticky = tk.W + tk.E )
		quitBut.grid( rowspan = 2 )

