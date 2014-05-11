# script to change keyboard brightness

# needs root priv
# add this to sudoers for command to work
# your_user	ALL= NOPASSWD: /path/to/kbdillum.sh
# must be run with sudo afterwards

#!/bin/bash

kbd_brightness=$(cat /sys/class/leds/samsung::kbd_backlight/brightness)
max_brightness=$(cat /sys/class/leds/samsung::kbd_backlight/max_brightness)
brightness_file="/sys/class/leds/samsung::kbd_backlight/brightness"
off=0
notify="please"
notify_icon="/usr/share/icons/HighContrast/scalable/emblems/emblem-system.svg"

kbdillumdown() {
	if [ $kbd_brightness -le $off ]; then
		exit;
	else
		echo $(expr $kbd_brightness - 1) > $brightness_file
	fi

	if [ "$notify" = please ]; then
		notify-send "Keyboard Backlight" "$(expr $kbd_brightness - 1) / $max_brightness" -i $notify_icon
	fi
}

kbdillumup() {
	if [ $kbd_brightness -ge $max_brightness ]; then
		exit
	else
		echo $(expr $kbd_brightness + 1) > $brightness_file
	fi

	if [ "$notify" = please ]; then
		notify-send "Keyboard Backlight" "$(expr $kbd_brightness + 1) / $max_brightness" -i $notify_icon
	fi
}

kbdillummax() {
	echo $max_brightness > $brightness_file

	if [ "$notify" = please ]; then
		notify-send "Keyboard Backlight" "$max_brightness / $max_brightness" -i $notify_icon
	fi

	exit
}

kbdillumoff() {
	echo $off > $brightness_file

	if [ "$notify" = please ]; then
		notify-send "Keyboard Backlight" "$off / $max_brightness" -i $notify_icon
	fi

	exit
}

if [ $(id -u) -eq 0 ]; then
	case "$1" in
		up)
			kbdillumup;;
		down)
			kbdillumdown;;
		max)
			kbdillummax;;
		off)
			kbdillumoff;;
		*)
			echo "Usage: sudo $0 {up | down | max | off}"
			exit 0;;
	esac
else
	echo "This script is ineffective without root priveledges"
	exit
fi

exit 0
