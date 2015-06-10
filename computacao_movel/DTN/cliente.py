import os
import json
import time
import socket
from threading import Thread

def conectar():
    soquete = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soquete.connect(('localhost', 5555))
    return soquete

def put_file(arq):
    print arq
    soquete = conectar()
    soquete.send('PUT')
    print soquete.recv(1024)
    soquete.send(arq)
    env = soquete.recv(1024)
    print env
    if env == 'TRUE':
        fp = open('/etc/black/carro/arquivos/{0}'.format(arq), 'r')
        strng = fp.read(1024)
        while strng:
            soquete.send(strng)
            strng = fp.read(1024)
    soquete.close()

def get_file(arq):
    print arq
    soquete = conectar()
    soquete.send('GET')
    soquete.send(arq)
    arquivo = open('/etc/black/carro/arquivos/{0}'.format(arq), 'w')
    while 1:
        dados = soquete.recv(1024)
        if not dados:
            break
        arquivo.write(dados)
    arquivo.close()
    soquete.close()


print 'Cliente de Arquivos Iniciou...'
ass = os.listdir('/etc/black/carro/arquivos/')
for i in ass:
    Thread(target=put_file, args=(i)).start()

while True:
    soquete = conectar()
    soquete.send('LIST')
    arqs = json.loads(soquete.recv(1014))
    soquete.close()
    ass = os.listdir('/etc/black/carro/arquivos/')
    for i in arqs:
        if i not in ass:
            Thread(target=get_file, args=(i, )).start()
    time.sleep(5)