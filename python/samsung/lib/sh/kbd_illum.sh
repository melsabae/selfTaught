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
notify_icon="/usr/share/icons/gnome/scalable/status/keyboard-brightness-symbolic.svg"

kbdillumdown() {
	if [ $kbd_brightness -le $off ]; then
		exit;
	else
		echo $(expr $kbd_brightness - 1) > $brightness_file
	fi
}

kbdillumup() {
	if [ $kbd_brightness -ge $max_brightness ]; then
		exit
	else
		echo $(expr $kbd_brightness + 1) > $brightness_file
	fi
}

kbdillummax() {
	echo $max_brightness > $brightness_file
}

kbdillumoff() {
	echo $off > $brightness_file
}

notify() {
	if [ "$notify" = please ]; then
		notify-send "Keyboard Backlight" "$(cat $brightness_file) / $max_brightness" -i $notify_icon
	fi
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
		[aA-zZ]*)
			echo "Usage: sudo $0 {up,down,max,off}"
			exit 0;;
		*)
			echo "Usage: sudo $0 {up,down,max,off}"
			exit 0;;
	esac

	notify
else
	echo "This script is ineffective without root priveledges"
fi

exit 0
