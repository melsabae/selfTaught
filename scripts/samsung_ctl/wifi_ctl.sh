wifi_state=$(grep -l 'wlan' /sys/devices/platform/samsung/rfkill/rfkill*/name | sed -e 's_\(.*\)name.*_\1_g')state
notify="please"
notify_on="/usr/share/icons/gnome/scalable/status/network-wireless-signal-excellent-symbolic.svg"
notify_off="/usr/share/icons/gnome/scalable/status/network-wireless-signal-none-symbolic.svg"

if [ "$notify" = please ]; then
	if [ $(cat $wifi_state) -eq 0 ]; then
		echo 1 > $wifi_state
		notify-send "Wi-Fi" "Turned On " -i $notify_on
	else
		echo 0 > $wifi_state
		notify-send "Wi-Fi" "Turned Off" -i $notify_off
	fi
else
	if [ $(cat $wifi_state) -eq 0 ]; then
		echo 1 > $wifi_state
	else
		echo 0 > $wifi_state
	fi
fi

exit 0
