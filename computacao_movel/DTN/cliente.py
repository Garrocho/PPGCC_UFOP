import os
import json
import time
import socket
from threading import Thread

def conectar():
    soquete = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soquete.connect(('localhost', 5555))
    return soquete

ass = os.listdir('/etc/black/carro/arquivos/')
for i in ass:
    print i
    soquete = conectar()
    soquete.send('PUT')
    print soquete.recv(1024)
    soquete.send(i)
    env = soquete.recv(1024)
    print env
    if env == 'TRUE':
        fp = open('/etc/black/carro/arquivos/{0}'.format(i), 'r')
        strng = fp.read(1024)
        while strng:
            soquete.send(strng)
            strng = fp.read(1024)
    soquete.close()

while True:
    soquete = conectar()
    soquete.send('LIST')
    arqs = json.loads(soquete.recv(2014))
    soquete.close()
    ass = os.listdir('/etc/black/carro/arquivos/')
    for i in arqs:
        if i not in ass:
            print i
            soquete = conectar()
            soquete.send('GET')
            soquete.send(i)
            arq = open('/etc/black/carro/arquivos/{0}'.format(i), 'w')
            while 1:
                dados = soquete.recv(1024)
                if not dados:
                    break
                arq.write(dados)
            arq.close()
            soquete.close()
    time.sleep(5)