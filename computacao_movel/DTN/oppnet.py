import os
import time
import subprocess
import commands
from random import randint
from easyprocess import Proc
from threading import Thread


def infraestruturar(wlan):
	print "INICIANDO PONTO DE ACESSO"
	os.system("ifconfig {0} 10.10.0.1/24".format(wlan))
	os.system("service isc-dhcp-server start")
	os.system("echo 1 > /proc/sys/net/ipv4/ip_forward")
	os.system("iptables -t nat -A POSTROUTING -s 10.10.0.0/16 -o ppp0 -j MASQUERADE")
	os.system("/usr/bin/create_ap -g 10.10.0.1 {0} eth0 BLACKBOX blackbox &".format(wlan))
	time.sleep(2)

def connectar(wlan):
	print 'ESCANEANDO REDES'
	os.system('/home/charles/Net-Opp/wpa-connect.sh &')
	tempo = randint(2, 5)
	while tempo > 0:
		print 'TENTANDO OBTER ENDERECO IP'
		os.system('timeout 10 dhclient {0}'.format(wlan))
		a = os.system("fping -c1 -t500 10.10.0.1")
		print a
		if a != 0:
			tempo = tempo - 1
		else:
			return 0
	return -1

wlan="wlan2"
os.system("killall -9 /usr/bin/create_ap")
os.system("killall -9 create_ap")
os.system("killall -9 hostapd")
os.system("killall -9 dnsmasq")
os.system("ifconfig " + wlan + " down")
os.system("ifconfig " + wlan + " up")
os.system("ifconfig " + wlan + " 10.15.0.1")
while True:
	if os.system("fping -c1 -t500 10.10.0.1") != 0:
		if connectar(wlan) != 0:
			os.system('killall -9 wpa-connect.sh')
			os.system('killall -9 /sbin/wpa_supplicant')
			print 'DESCONECTADO DA REDE'
			infraestruturar(wlan)
			tempo = randint(6, 10)
			while tempo > 0:
				print "ENTREI - " + str(tempo)
				a=Proc('arp-scan --interface={0} --localnet'.format(wlan)).call(timeout=2).stdout
				print a
				if "10.10.0." in a:
					tempo = 7
				else:
					tempo = tempo - 1
				time.sleep(2)
			os.system("killall -9 /usr/bin/create_ap")
			os.system("killall -9 create_ap")
			os.system("killall -9 hostapd")
			os.system("killall -9 dnsmasq")
			os.system("ifconfig {0} down".format(wlan))
			os.system("ifconfig {0} up".format(wlan))
			os.system("ifconfig {0} 10.15.0.1".format(wlan))
	else:
		print 'CONECTADO A REDE'
		time.sleep(2)