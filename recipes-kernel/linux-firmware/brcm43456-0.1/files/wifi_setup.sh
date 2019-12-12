#!/bin/sh
wpa_supplicant -Dnl80211 -i wlan0 -c /etc/wpa_supplicant.conf -d&
udhcpc -i wlan0

