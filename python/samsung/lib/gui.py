import dev_manip as dm
import dev_ctl as dc
import Tkinter as tk
import tkMessageBox

class form( tk.Tk ):
	def __init__( self, parent ):
		tk.Tk.__init__( self, parent )
		self.parent = parent
		self.initialize()

	def PerfSet( self, value ):
		try:
			return dc.SetState( self.perf_dev, value )
		except IOError:
			tkMessageBox.showerror( 'IOError', 'Unable to write to device file.\nThis is likely due to insufficient privileges.' )

	def RangeSet( self, device, value, maxFile ):
		try:
			# wtb python 2.7 switch statements
			if value == 'max':
				return dc.Max( device, maxFile )
			elif value == 'off':
				return dc.SetState( device, '0' )
			elif value == 'up':
				return dc.Up( device, maxFile )
			elif value == 'down':
				return dc.Down( device, '0' )
			else:
				return False
		except IOError:
			tkMessageBox.showerror( 'IOError', 'This is likely due to insufficient priveledges.', default = tkMessageBox.OK )


	def OnOff( self, device, value ):
		try:
			if value == 'on':
				value = '1'
				return dc.SetState( device, value )
			elif value == 'off':
				value = '0'
				return dc.SetState( device, value )
			else:
				return False
		except IOError:
			tkMessageBox.showerror( 'IOError', 'This is likely due to insufficient priveledges.', default = tkMessageBox.OK )

	def initialize( self ):
		self.grid()
		self.title( 'Samsung Series9 Fn Control' )

		# brings device file paths into UI from dm
		self.perf_dev = dm.perf_level
		self.kbd_dev = dm.kbd_bright
		self.kbd_max = dm.kbd_maxBright
		self.wifi_dev = dm.wlan
		self.bt_dev = dm.bt
		self.batt_dev = dm.batt_extend
		self.usb_dev = dm.usb_charge
		self.mon_dev = dm.mon_bright
		self.mon_max = dm.mon_maxBright

		# contains all legal options for all hardware referenced
			# on my machine
		# not all hardware will use the entire list
		# might like to implement a min feature later
		controlOpts = ( 'on', 'off', 'max',
				'up', 'down', 'silent', 'normal' )

		# default options to show on option menus
		# also contains variables to reference upon button clicks
		perf = tk.StringVar()
		kbd = tk.StringVar()
		wifi = tk.StringVar()
		bt = tk.StringVar()
		batt = tk.StringVar()
		usb = tk.StringVar()
		mon = tk.StringVar()
		kbd_bar_val = tk.StringVar()
		perf.set( controlOpts[ 5 ])
		kbd.set( controlOpts[ 1 ])
		wifi.set( controlOpts[ 0 ])
		bt.set( controlOpts[ 1 ])
		batt.set( controlOpts[ 0 ])
		usb.set( controlOpts[ 1 ])
		mon.set( controlOpts[ 1 ])
		kbd_bar_val.set( '0' )

		perfOpts = tk.OptionMenu( self, perf, *controlOpts[ 5:7 ])
		perfOpts.grid( column = 1, row = 0, sticky = tk.W + tk.E )
		# lambda keeps Tkinter from executing on instantiation
		perfBut = tk.Button( self, text = "Performance Level",
				command = lambda:
				self.PerfSet( perf.get() ))
		perfBut.grid( column = 0, row = 0, sticky = tk.W + tk.E )

		kbdOpts = tk.OptionMenu( self, kbd, *controlOpts[ 1:5 ])
		kbdOpts.grid( column = 1, row = 1, sticky = tk.W + tk.E )
		kbdBut = tk.Button( self, text = "Keyboard Backlight", 
				command = lambda:
				self.RangeSet( self.kbd_dev, kbd.get(),
					self.kbd_max ))
		kbdBut.grid( column = 0, row = 1, sticky = tk.W + tk.E )

		wifiOpts = tk.OptionMenu( self, wifi, *controlOpts[ :2 ])
		wifiOpts.grid( column = 1, row = 2, sticky = tk.W + tk.E )
		wifiBut = tk.Button( self, text = "Wi-Fi Control", 
				command = lambda:
				self.OnOff( self.wifi_dev, wifi.get() ))
		wifiBut.grid( column = 0, row = 2, sticky = tk.W + tk.E )

		btOpts = tk.OptionMenu( self, bt, *controlOpts[ :2 ])
		btOpts.grid( column = 1, row = 3, sticky = tk.W + tk.E )
		btBut = tk.Button( self, text = "Bluetooth Control",
				command = lambda:
				self.OnOff( self.bt_dev, bt.get() ))
		btBut.grid( column = 0, row = 3, sticky = tk.W + tk.E )

		battOpts = tk.OptionMenu( self, batt, *controlOpts[ :2 ])
		battOpts.grid( column = 1, row = 4, sticky = tk.W + tk.E )
		battBut = tk.Button( self, text = "Battery Life Extender",
				command = lambda:
				self.OnOff( self.batt_dev, batt.get() ))
		battBut.grid( column = 0, row = 4, sticky = tk.W + tk.E )

		usbOpts = tk.OptionMenu( self, usb, *controlOpts[ :2 ])
		usbOpts.grid( column = 1, row = 5, sticky = tk.W + tk.E )
		usbBut = tk.Button( self, text = "USB Charging While Off",
				command = lambda:
				self.OnOff( self.usb_dev, usb.get() ))
		usbBut.grid( column = 0, row = 5, sticky = tk.W + tk.E )

		monOpts = tk.OptionMenu( self, mon, *controlOpts[ 1:5 ])
		monOpts.grid( column = 1, row = 6, sticky = tk.W + tk.E )
		monBut = tk.Button( self, text = "Monitor Brightness",
				command = lambda:
				self.RangeSet( self.mon_dev, mon.get(),
					self.mon_max ))
		monBut.grid( column = 0, row = 6, sticky = tk.W + tk.E )

		quitBut = tk.Button( self, text = "Quit", command = quit )
		quitBut.grid( column = 0, row = 7, sticky = tk.W + tk.E )
		quitBut.grid( rowspan = 2 )

		kbd_bar = tk.Scale( self,
				from_ = 0,
				to = dm.ReadValue( self.kbd_max ),
				resolution = 1,
				orient = tk.HORIZONTAL,
				tickinterval = 4,
				variable = self.kbd_bar_val,
				command = dm.WriteValue( self.kbd_dev,
					self.kbd_bar_val )
				)
		kbd_bar.grid( column = 3,
				row = 1,
				sticky = tk.W + tk.E
				)

