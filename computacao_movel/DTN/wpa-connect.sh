#!/bin/bash
ifconfig wlan2 down
ifconfig wlan2 up
wpa_supplicant -d -i wlan2 -D nl80211 -c /home/charles/workspace/MCC/computacao_movel/DTN/wpa.conf >> /dev/null
