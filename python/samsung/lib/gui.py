import Tkinter as tk
import dev_manip as dm

class form(tk.Tk):
	def __init__(self, parent):
		tk.Tk.__init__(self, parent)
		self.parent = parent
		self.initialize()

	def TestVars(self, var):
		print var

	def initialize(self):
		self.grid()
		self.title('Samsung Series9 Fn Control')

		# contains all legal options for all hardware referenced
		# not all hardware will use the entire list
		controlOpts = ( 'on', 'off', 'up',
				'down', 'max', 'silent', 'normal' )

		perfBut = tk.Button( self, text="Performance Level" )
		perfBut.grid( column = 0, row = 0, sticky = tk.W + tk.E )
		perfBut.rowconfigure( 0, weight=1 )
		perfBut.columnconfigure( 0, weight=1 )
		perf = tk.StringVar()
		perf.set( controlOpts[ 5 ])
		perfOpts = tk.OptionMenu( self, perf, *controlOpts[ 5:7 ])
		perfOpts.grid( column = 1, row = 0, sticky = tk.W + tk.E )

		kbdBut = tk.Button( self, text="Keyboard Backlight" )
		kbdBut.grid( column = 0, row = 1, sticky = tk.W + tk.E )
		kbd = tk.StringVar()
		kbd.set( controlOpts[ 1 ])
		kbdOpts = tk.OptionMenu( self, kbd, *controlOpts[ 1:5 ])
		kbdOpts.grid( column = 1, row = 1, sticky = tk.W + tk.E )

		wifiBut = tk.Button( self, text="Wi-Fi Control" )
		wifiBut.grid( column = 0, row = 2, sticky = tk.W + tk.E )
		wifi = tk.StringVar()
		wifi.set( controlOpts[ 0 ])
		wifiOpts = tk.OptionMenu( self, wifi, *controlOpts[ :2 ])
		wifiOpts.grid( column = 1, row = 2, sticky = tk.W + tk.E )

		btBut = tk.Button( self, text="Bluetooth Control" )
		btBut.grid( column = 0, row = 3, sticky = tk.W + tk.E )
		bt = tk.StringVar()
		bt.set( controlOpts[ 1 ])
		btOpts = tk.OptionMenu( self, bt, *controlOpts[ :2 ])
		btOpts.grid( column = 1, row = 3, sticky = tk.W + tk.E )

		battBut = tk.Button( self, text="Battery Life Extender" )
		battBut.grid( column = 0, row = 4, sticky = tk.W + tk.E )
		batt = tk.StringVar()
		batt.set( controlOpts[ 0 ])
		battOpts = tk.OptionMenu( self, batt, *controlOpts[ :2 ])
		battOpts.grid( column = 1, row = 4, sticky = tk.W + tk.E )

		usbBut = tk.Button( self, text="USB Charging While Off" )
		usbBut.grid( column = 0, row = 6, sticky = tk.W + tk.E )
		usb = tk.StringVar()
		usb.set( controlOpts[ 1 ])
		usbOpts = tk.OptionMenu( self, usb, *controlOpts[ :2 ])
		usbOpts.grid( column = 1, row = 6, sticky = tk.W + tk.E )


		quitBut = tk.Button( self, text="Quit", command = quit )
		quitBut.grid( column = 0, row = 7, sticky = tk.W + tk.E )
		quitBut.grid( rowspan = 2 )

