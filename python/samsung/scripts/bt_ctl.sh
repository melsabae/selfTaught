#!/bin/bash

bt_state="$(grep -l 'bluetooth' /sys/devices/platform/samsung/rfkill/rfkill*/name | sed -e 's_\(.*\)name.*_\1_g')state"
notify="please"
notify_on="/usr/share/icons/gnome/scalable/status/bluetooth-active-symbolic.svg"
notify_off="/usr/share/icons/gnome/scalable/status/bluetooth-disabled-symbolic.svg"

notify() {
	if [ "$notify" = please ]; then
		if [ $(cat $bt_state) -eq 0 ]; then
			notify-send "Bluetooth" "Turned off" -i $notify_off
		else
			notify-send "Bluetooth" "Turned on " -i $notify_on
		fi
	fi
}

turn_on() {
	echo 1 > $bt_state
}

turn_off() {
	echo 0 > $bt_state
}

toggle() {
	if [ $(cat $bt_state) -eq 0 ]; then
		turn_on
	else
		turn_off
	fi
}

if [ $(id -u) -eq 0 ]; then
	case "$1" in
		on)
			turn_on;;
		off)
			turn_off;;
		toggle)
			toggle;;
		[aA-zZ]*)
			echo "Usage: sudo $0 {on,off,toggle}";
			exit;;
		*)
			toggle;;
	esac

	notify
else
	echo "This script is ineffective without root priveledges."
fi

exit 0
