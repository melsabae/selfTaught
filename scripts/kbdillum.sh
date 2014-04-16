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
		echo "Keyboard backlight script"
		echo "Usage: sudo $0 {up | down | max | off}"
		exit 0;;
esac

exit 0
