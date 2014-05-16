import Tkinter
import proc_manip as pm

class form(Tkinter.Tk):
	def __init__(self, parent):
		Tkinter.Tk.__init__(self, parent)
		self.parent = parent
		self.initialize()

	def PerfChange(self):
		pm.ExecScript( pm.GetPath( pm.perf_level ))

	def KbdillumChange(self):
		pm.ExecScript( pm.GetPath( pm.kbd_illum ))

	def BluetoothChange(self):
		pm.ExecScript( pm.GetPath( pm.bt_ctl ))

	def WifiChange(self):
		pm.ExecScript( pm.GetPath( pm.wifi_ctl ))

	def initialize(self):
		self.grid()
		self.title('Samsung Series9 Fn Control')

		perfButton = Tkinter.Button( self, text="Performance Level", command=self.PerfChange )
		perfButton.grid(column=0, row=0)

		kbdButton = Tkinter.Button( self, text="Keyboard Backlight", command=self.KbdillumChange )
		kbdButton.grid(column=0, row=1)

		wifiButton = Tkinter.Button( self, text="Bluetooth Control", command=self.BluetoothChange )
		wifiButton.grid(column=0, row=2)

		btButton = Tkinter.Button( self, text="Wi-Fi Control", command=self.WifiChange )
		btButton.grid(column=0, row=3)
