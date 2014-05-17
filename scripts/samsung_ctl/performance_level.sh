# script switches performance_level of samsung series 9 laptop
# valid values are {silent | normal}

# will require root privs to run
# add your_user	ALL= NOPASSWD: /path/to/performance_level.sh
# and you can run this just fine with sudo

#!/bin/bash

current_level=$(cat /sys/devices/platform/samsung/performance_level)
performance_file="/sys/devices/platform/samsung/performance_level"
notify="please"
notify_icon="/usr/share/icons/gnome/scalable/categories/preferences-system-symbolic.svg"

toggle() {
	case $current_level in
		silent)
			echo "normal" > $performance_file;;
		normal)
			echo "silent" > $performance_file;;
	esac
}

if [ $(id -u) -eq 0 ]; then
	case "$1" in
		silent)
			echo "silent" > $performance_file;;
		normal)
			echo "normal" > $performance_file;;
		toggle)
			toggle;;
		[aA-zZ]*)
			echo "Usage: sudo $0 {silent,normal,toggle}";
			exit;;
		*)
			toggle;;
	esac

	if [ "$notify" = please ]; then
		# you're most welcome :)
		notify-send "Performance Level" "'$(cat $performance_file)'" -i $notify_icon
	fi
else
	echo "This script is ineffective without root priveledges."
fi

exit 0
