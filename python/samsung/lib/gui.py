import Tkinter
import dev_manip as dm

class form(Tkinter.Tk):
	def __init__(self, parent):
		Tkinter.Tk.__init__(self, parent)
		self.parent = parent
		self.initialize()

	def Notify():
		pass

	def PerfChange(self):
		self.Notify()

	def KbdillumChange(self):
		self.Notify()

	def BluetoothChange(self):
		self.Notify()

	def WifiChange(self):
		self.Notify()

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

		quitButton = Tkinter.Button( self, text="Quit", command=self.quit )
		quitButton.grid(column=0, row=4)

