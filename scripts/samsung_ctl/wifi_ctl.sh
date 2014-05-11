wifi_state=$(grep -l 'wlan' /sys/devices/platform/samsung/rfkill/rfkill*/name | sed -e 's_\(.*\)name.*_\1_g')state


if [ $(cat $wifi_state) -eq 0 ]; then
	echo 1 > $wifi_state
else
	echo 0 > $wifi_state
fi

exit 0
