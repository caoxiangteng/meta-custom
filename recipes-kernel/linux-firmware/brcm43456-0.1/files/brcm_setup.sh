#/bin/sh
echo 0 > /sys/class/rfkill/rfkill2/state
echo 1 > /sys/class/rfkill/rfkill2/state

brcm_patchram_plus -d --enable_hci --no2bytes --tosleep 200000 --baudrate 3000000 --patchram /lib/firmware/bcm/APM_BCM43456/bcmdhd.hcd /dev/ttymxc2 &
sleep 10
rfkill unblock bluetooth
hciconfig hci0 up

wpa_supplicant -Dnl80211 -i wlan0 -c /etc/wpa_supplicant.conf -d&
