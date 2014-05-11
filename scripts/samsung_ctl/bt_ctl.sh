bt_state=$(grep -l 'bluetooth' /sys/devices/platform/samsung/rfkill/rfkill*//name | sed -e 's_\(.*\)name.*_\1_g')state

if [ $(cat $bt_state) -eq 0 ]; then
	echo 1 > $bt_state
else
	echo 0 > $bt_state
fi

exit 0
