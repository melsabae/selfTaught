#!/bin/bash

wifi_state="$(grep -l 'wlan' /sys/devices/platform/samsung/rfkill/rfkill*/name | sed -e 's_\(.*\)name.*_\1_g')state"
notify="please"
notify_on="/usr/share/icons/gnome/scalable/status/network-wireless-signal-excellent-symbolic.svg"
notify_off="/usr/share/icons/gnome/scalable/status/network-wireless-signal-none-symbolic.svg"

notify() {
	if [ "$notify" = please ]; then
		if [ $(cat $wifi_state) -eq 0 ]; then
			notify-send "Wi-Fi" "Turned off" -i $notify_off
		else
			notify-send "Wi-Fi" "Turned on " -i $notify_on
		fi
	fi
}

turn_on() {
	rfkill unblock wlan
}

turn_off() {
	rfkill block wlan
}

toggle() {
	if [ $(cat $wifi_state) -eq 0 ]; then
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
			echo "Usage sudo $0 {on,off,toggle}";
			exit;;
		*)
			toggle;;
	esac

	notify
else
	echo "This script is ineffective without root priveledges."
fi

exit 0
