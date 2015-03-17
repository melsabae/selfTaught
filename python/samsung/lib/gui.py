import os
import Tkinter as tk
import tkMessageBox
import dev_obj as doj

class form( tk.Tk ):
    def __init__( self, parent ):
        tk.Tk.__init__( self, parent )
        self.parent = parent
        # filthy handling, not comprehensive
        try: 
            self.initialize()
        except IOError:
            pass
        except OSError:
            pass

    def initialize( self ):
        self.grid()
        self.title( 'Samsung Series9 Fn Control' )

        # *_dev are hardware devices
        # constructor:
        # name, optional replacename, path, on value, off value, optional readstring

        # for example: look for a file named performance_level, replace 'performance_level' with nothing, start searching in doj.samsung as toplevel dir, 'on' value is string 'normal', 'off' value is string 'silent', we have a blank option so no file reading needs to be done to find it 'performance_level'
        perf_dev = doj.Device( 'performance_level', '',
            doj.samsung, 'normal', 'silent', '' )
        batt_dev = doj.Device( 'battery_life_extender', '',
            doj.samsung, '1', '0', '' )
        usb_dev = doj.Device( 'usb_charge', '',
            doj.samsung, '1', '0', '' )
        # look for a file named 'name', in the end replace 'name' with 'state', start searching in doj.samsung, 1 is on, 0 is off, and identify which name file by reading string 'samsung-wlan' from 'name'
        wifi_dev = doj.Device( 'name', 'state',
            doj.samsung, '1', '0', 'samsung-wlan' )
        bt_dev = doj.Device( 'name', 'state',
            doj.samsung, '1', '0', 'samsung-bluetooth' )

        # constructor:
        # name, optional replace, path, max value, off value, optional readstring
        kbd_dev = doj.RangeDevice( 'brightness', '',
            doj.samsung, '8', '0', '' )
        mon_dev = doj.RangeDevice( 'brightness', '',
            doj.monitor, '100', '0', '' )

        # variables: increment, file with maximum value, decrement
        kbd_dev.SetBounds( '1', 'max_brightness', '1' )
        mon_dev.SetBounds( '1', 'max_brightness', '1' )

        # contains options for hardware, not all are used by all hardware, not all hardware will use this list either
        # and the hardware that uses this list will not necessarily use all options
        controlOpts = ( 'on', 'off', 'max',
            'up', 'down', 'silent', 'normal' )

        # variables here are referenced by the gui widgets
        perf = tk.StringVar()
        wifi = tk.StringVar()
        bt = tk.StringVar()
        batt = tk.StringVar()
        usb = tk.StringVar()
        kbd = tk.StringVar()
        mon = tk.StringVar()

        # states hash table, keeps the stringvar.set valuables tidy
        states = {
                'silent': 'silent',
                'performance': 'performance',
                'on': 'on',
                '1': 'on',
                'off': 'off',
                '0': 'off',
                }

        # defaults each combobox to whatever machine has set
        # also keeps devices from changing state when starting up, if the command event fires
        perf.set( states[ perf_dev.Read() ])
        wifi.set( states[ wifi_dev.Read() ])
        bt.set( states[ bt_dev.Read() ])
        batt.set( states[ batt_dev.Read() ])
        usb.set( states[ usb_dev.Read() ])
        kbd.set( kbd_dev.Read() )
        mon.set( mon_dev.Read() )
        buttons = []

        # Opts are option menus, Buts are buttons, Bars are scales
        perfOpts = tk.OptionMenu( self, perf, *controlOpts[ 5:7 ])
        perfOpts.grid( column = 1, row = 0, sticky = tk.W + tk.E )
        # lambda keeps Tkinter from executing only once on instantiation
        perfBut = tk.Button( self, text = "Performance Level",
            state = 'disabled',
            command = lambda:
            perf_dev.Write( perf.get() ))
        perfBut.grid( column = 0, row = 0, sticky = tk.W + tk.E )
        buttons.append( perfBut )

        wifiOpts = tk.OptionMenu( self, wifi, *controlOpts[ :2 ])
        wifiOpts.grid( column = 1, row = 1, sticky = tk.W + tk.E )
        wifiBut = tk.Button( self, text = "Wi-Fi Power", 
            state = 'disabled',
            command = lambda:
                wifi_dev.Write( wifi.get() ))
        wifiBut.grid( column = 0, row = 1, sticky = tk.W + tk.E )
        buttons.append( wifiBut )

        btOpts = tk.OptionMenu( self, bt, *controlOpts[ :2 ])
        btOpts.grid( column = 1, row = 2, sticky = tk.W + tk.E )
        btBut = tk.Button( self, text = "Bluetooth Power",
                state = 'disabled',
                command = lambda:
                bt_dev.Write( bt.get() ))
        btBut.grid( column = 0, row = 2, sticky = tk.W + tk.E )
        buttons.append( btBut )

        battOpts = tk.OptionMenu( self, batt, *controlOpts[ :2 ])
        battOpts.grid( column = 1, row = 3, sticky = tk.W + tk.E )
        battBut = tk.Button( self, text = "Battery Life Extender",
                state = 'disabled',
                command = lambda:
                batt_dev.Write( batt.get() ))
        battBut.grid( column = 0, row = 3, sticky = tk.W + tk.E )
        buttons.append( battBut )

        usbOpts = tk.OptionMenu( self, usb, *controlOpts[ :2 ])
        usbOpts.grid( column = 1, row = 4, sticky = tk.W + tk.E )
        usbBut = tk.Button( self, text = "USB Charging While Off",
                state = 'disabled',
                command = lambda:
                usb_dev.Write( usb.get() ))
        usbBut.grid( column = 0, row = 4, sticky = tk.W + tk.E )
        buttons.append( usbBut )

        kbdBut = tk.Button( self, text = "Keyboard Backlight" )
        kbdBut.grid( column = 0, row = 5, sticky = tk.W + tk.E )

        # kbd backlight seems to have a delay for a fade in/out effect, so quick fiddling with the slider may cause it to not correctly set what value you want
        kbd_bar = tk.Scale( self,
            state = 'disabled',
            from_ = 0,
            to = kbd_dev.maxVal,
            resolution = kbd_dev.increment,
            orient = tk.HORIZONTAL,
            tickinterval = int( kbd_dev.maxVal ) / 2,
            variable = kbd,
            # val is what is passed by scale's command
            command = lambda val:
            kbd_dev.Write( val ))

        kbd_bar.grid( column = 1, row = 5, sticky = tk.W + tk.E )
        buttons.append( kbd_bar )

        monBut = tk.Button( self, text = "Monitor Brightness" )
        monBut.grid( column = 0, row = 6, sticky = tk.W + tk.E )

        mon_bar = tk.Scale( self,
            state = 'disabled',
            from_ = 0,
            to = mon_dev.maxVal,
            resolution = mon_dev.increment,
            orient = tk.HORIZONTAL,
            tickinterval = int( mon_dev.maxVal ) / 2,
            variable = mon,
            command = lambda val:
            mon_dev.Write( val ))

        mon_bar.grid( column = 1, row = 6, sticky = tk.W + tk.E )
        buttons.append( mon_bar )

        quitBut = tk.Button( self, text = "Quit", command = quit )
        quitBut.grid( column = 0, row = 7, sticky = tk.W + tk.E )
        quitBut.grid( rowspan = 2 )

        # warns that controls are disabled if not root, as instantiated
        # else enables them if user has root privs
        if os.getuid() != 0:
            tkMessageBox.showwarning( 'Insufficient Priviledges.', 'Your user does not have write permission on files located in /sys. Controls have been disabled.', parent = None )
        else:
            for button in buttons:
                button.config( state = 'normal' )

