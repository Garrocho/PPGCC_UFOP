#!/usr/bin/env python
# coding: utf-8
import sys
import time
import psutil


def analisa_argumentos():
	if len(sys.argv) >= 4:
		argumentos = []
		if sys.argv[1] == '-pid':
			try:
				argv_int = int(sys.argv[2])
				argumentos.append(argv_int)
			except:
				pass
		if sys.argv[3] == '-i':
			try:
				argv_int = int(sys.argv[4])
				argumentos.append(argv_int)
			except:
				pass
		if sys.argv[5] == '-d':
			try:
				argv_int = int(sys.argv[6])
				argumentos.append(argv_int)
			except:
				pass		
		if len(argumentos) == 3:
			return argumentos
	print 'Argumentos Inválidos...\nUtilize: ./analise.py -pid <id_do_processo> -i <intervalo> -d <duracao>'
	print '<id_do_processo> é pid de um processo.\n<i> é o intervalo de tempo para analise.\n<d> é a duração da análise.'
	sys.exit(0)


def obter_nome_processo(pid):
	try:
		processo = psutil.Process(pid)
	except:
		print 'Processo', pid, 'não encontrado.'
		sys.exit(0)
	return processo.name()


def obter_cpu_e_mem_atual(pid):
	try:
		processo = psutil.Process(pid)
	except:
		print 'Processo', pid, 'não encontrado.'
		sys.exit(0)
	if processo.is_running():
		por_cpu = processo.cpu_percent(interval=1.0)
		por_mem = processo.memory_percent()
		return [por_cpu, por_mem]
	print 'O processo', pid, 'parou de executar.'
	return None


def processa_lista_cpu_mem(lista, intervalo, duracao):
	soma_cpu = 0
	soma_mem = 0
	tam_lista = len(lista)
	for i in lista:
		soma_cpu += i[0]
		soma_mem += i[1]

	print 'DURAÇÃO: %d\tINTERVALO: %d' % (duracao, intervalo)
	print 'CPU:', soma_cpu/tam_lista, '%'
	print 'MEMÓRIA: %.2f %s' % (soma_mem/tam_lista, '%')


if __name__ == '__main__':
	pid, intervalo, duracao = analisa_argumentos()
	lista_cpu_mem = []
	nome_processo = obter_nome_processo(pid)
	print 'Analisando o %s...' % nome_processo

	if duracao == -1:
		while True:
			cpu_e_mem = obter_cpu_e_mem_atual(pid)
			if cpu_e_mem == None:
				break
			else:
				lista_cpu_mem.append(cpu_e_mem)
			time.sleep(intervalo)
	else:
		for i in range(duracao):
			cpu_e_mem = obter_cpu_e_mem_atual(pid)
			if cpu_e_mem == None:
				break
			else:
				lista_cpu_mem.append(cpu_e_mem)
			time.sleep(intervalo)
	processa_lista_cpu_mem(lista_cpu_mem, intervalo, duracao)