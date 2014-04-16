# script to change keyboard brightness by 1 increment
# needs root priv

# add this to sudoers for command to work
# saba = ALL: NOPASSWD: /path/to/kbdillum.sh
# must be run with sudo

#!/bin/bash

kbd_brightness=$(cat /sys/class/leds/samsung::kbd_backlight/brightness)
max_brightness=$(cat /sys/class/leds/samsung::kbd_backlight/max_brightness)
brightness_file="/sys/class/leds/samsung::kbd_backlight/brightness"
off=0

kbdillumdown() {
	if [ $kbd_brightness -le $off ]; then
		exit;
	else
		echo $(expr $kbd_brightness - 1) > $brightness_file
		exit
	fi
}

kbdillumup() {
	if [ $kbd_brightness -ge $max_brightness ]; then
		exit
	else
		echo $(expr $kbd_brightness + 1) > $brightness_file
		exit
	fi
}

kbdillummax() {
	echo $max_brightness > $brightness_file
	exit
}

kbdillumoff() {
	echo $off > $brightness_file
	exit
}

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
		# echo "Keyboard backlight toggle script"
		# echo "Usage: $0 {up | down | max | off}"
		exit 0;;
esac

exit 0
