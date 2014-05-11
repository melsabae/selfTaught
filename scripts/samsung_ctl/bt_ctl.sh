bt_state=$(grep -l 'bluetooth' /sys/devices/platform/samsung/rfkill/rfkill*/name | sed -e 's_\(.*\)name.*_\1_g')state
notify="please"
notify_on="/usr/share/icons/gnome/scalable/status/bluetooth-active-symbolic.svg"
notify_off="/usr/share/icons/gnome/scalable/status/bluetooth-disabled-symbolic.svg"

if [ "$notify" = please ]; then
	if [ $(cat $bt_state) -eq 0 ]; then
		echo 1 > $bt_state
		notify-send "Bluetooth" "Turned On " -i $notify_on
	else
		echo 0 > $bt_state
		notify-send "Bluetooth" "Turned Off" -i $notify_off
	fi
else
	if [ $(cat $bt_state) -eq 0 ]; then
		echo 1 > $bt_state
	else
		echo 0 > $bt_state
	fi
fi
exit 0
