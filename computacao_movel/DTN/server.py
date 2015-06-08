import os
import time
import socket
from json import loads
from threading import Thread

def trata_cliente(conexao, endereco):
    requisicao = conexao.recv(1024)
    if requisicao == 'LIST':
        arqs = of.listdir('/etc/black/carro/arquivos/')
        conexao.send(arqs)
    elif requisicao == 'GET':
        arquivo = conexao.recv(1024)
        arq = open(arquivo, 'w')
        tempos = 0
        while 1:
            dados = conexao.recv(1024)
            if not dados:
                break
            arq.write(dados)
        arq.close()
    conexao.close()


def loop_servidor():
    
    soquete = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soquete.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    soquete.bind(('10.10.0.1', 5555))
    soquete.listen(10)

    # Fica aqui aguardando novas conexoes.
    while True:

        # Para cada nova conexao e criado um novo processo para tratar as requisicoes.
        conexao = soquete.accept()
        novaConexao = []
        novaConexao.append(conexao[0])
        novaConexao.append(conexao[1])
        Thread(target=trata_cliente, args=(novaConexao)).start()


if __name__ == '__main__':
    print 'Servidor de Nomes Iniciou na Porta 5555'
    Thread(target=loop_servidor).start()