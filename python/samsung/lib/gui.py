import dev_manip as dm
import dev_ctl as dc
import Tkinter as tk

class form( tk.Tk ):
	def __init__( self, parent ):
		tk.Tk.__init__( self, parent )
		self.parent = parent
		self.initialize()
	
	def PerfSet( self, value ):
		return dc.SetState( self.perf_dev, value )

	def KbdIllumSet( self, value ):
		if value == 'max':
			return dc.Max( self.kbd_dev, dm.kbd_maxBright )
		elif value == 'off':
			return dc.SetState( self.kbd_dev, '0' )
		elif value == 'up':
			return dc.Up( self.kbd_dev, dm.kbd_maxBright )
		elif value == 'down':
			return dc.Down( self.kbd_dev, '0' )
		else:
			return False
	
	def OnOff( self, device, value ):
		if value == 'on':
			value = '1'
			return dc.Set( device, value )
		elif value == 'off':
			value = '0'
			return dc.Set( device, value )
		else:
			return False

	def TestVars( self, var ):
		print var

	def initialize( self ):
		self.grid()
		self.title( 'Samsung Series9 Fn Control' )

		# contains all legal options for all hardware referenced
		# not all hardware will use the entire list
		controlOpts = ( 'on', 'off', 'max',
				'up', 'down', 'silent', 'normal' )

		# brings device file paths into UI from dm
		self.perf_dev = dm.perf_level
		self.kbd_dev = dm.kbd_bright
		self.wifi_dev = dm.wlan
		self.bt_dev = dm.bt
		self.batt_dev = dm.batt_extend
		self.usb_dev = dm.usb_charge

		perf = tk.StringVar()
		# default selection is silent
		perf.set( controlOpts[ 5 ])
		perfOpts = tk.OptionMenu( self, perf, *controlOpts[ 5:7 ])
		perfOpts.grid( column = 1, row = 0, sticky = tk.W + tk.E )
		# lambda keeps Tkinter from executing on instantiation
		perfBut = tk.Button( self, text = "Performance Level",
				command = lambda:
				self.PerfSet( perf.get() ))
		perfBut.grid( column = 0, row = 0, sticky = tk.W + tk.E )

		kbd = tk.StringVar()
		kbd.set( controlOpts[ 1 ])
		kbdOpts = tk.OptionMenu( self, kbd, *controlOpts[ 1:5 ])
		kbdOpts.grid( column = 1, row = 1, sticky = tk.W + tk.E )
		kbdBut = tk.Button( self, text = "Keyboard Backlight", 
				command = lambda:
				self.KbdIllumSet( kbd.get() ))
		kbdBut.grid( column = 0, row = 1, sticky = tk.W + tk.E )

		wifi = tk.StringVar()
		wifi.set( controlOpts[ 0 ])
		wifiOpts = tk.OptionMenu( self, wifi, *controlOpts[ :2 ])
		wifiOpts.grid( column = 1, row = 2, sticky = tk.W + tk.E )
		wifiBut = tk.Button( self, text = "Wi-Fi Control", 
				command = lambda:
				self.OnOff( self.wifi, wifi.get() ))
		wifiBut.grid( column = 0, row = 2, sticky = tk.W + tk.E )

		bt = tk.StringVar()
		bt.set( controlOpts[ 1 ])
		btOpts = tk.OptionMenu( self, bt, *controlOpts[ :2 ])
		btOpts.grid( column = 1, row = 3, sticky = tk.W + tk.E )
		btBut = tk.Button( self, text = "Bluetooth Control",
				command = lambda:
				self.OnOff( self.bt, bt.get() ))
		btBut.grid( column = 0, row = 3, sticky = tk.W + tk.E )

		batt = tk.StringVar()
		batt.set( controlOpts[ 0 ])
		battOpts = tk.OptionMenu( self, batt, *controlOpts[ :2 ])
		battOpts.grid( column = 1, row = 4, sticky = tk.W + tk.E )
		battBut = tk.Button( self, text = "Battery Life Extender",
				command = lambda:
				self.OnOff( self.batt, batt.get() ))
		battBut.grid( column = 0, row = 4, sticky = tk.W + tk.E )

		usb = tk.StringVar()
		usb.set( controlOpts[ 1 ])
		usbOpts = tk.OptionMenu( self, usb, *controlOpts[ :2 ])
		usbOpts.grid( column = 1, row = 6, sticky = tk.W + tk.E )
		usbBut = tk.Button( self, text = "USB Charging While Off",
				command = lambda:
				self.OnOff( self.usb, usb.get() ))
		usbBut.grid( column = 0, row = 6, sticky = tk.W + tk.E )


		quitBut = tk.Button( self, text = "Quit", command = quit )
		quitBut.grid( column = 0, row = 7, sticky = tk.W + tk.E )
		quitBut.grid( rowspan = 2 )

