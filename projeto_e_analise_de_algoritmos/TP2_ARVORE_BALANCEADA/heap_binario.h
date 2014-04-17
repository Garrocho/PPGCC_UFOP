#ifndef HEAP_BINARIO_H
#define HEAP_BINARIO_H

#include "arvore_avl.h"

typedef struct
{
	Registro elementos;
	int tamanho;
	int tamanho_max;
}TipoHEAP;

void inicializar_heap(TipoHEAP *h, int tamanho);

void destruir_heap(TipoHEAP *h);

int heap_pai(int n);

int filho_esquerda(int n);

int filho_direita(int n);

void heap_imprimir(TipoHEAP h);

void heap_trocar(TipoHEAP *heap, int index, int index_to);

void heapear_subindo(TipoHEAP *heap, int index);

void arranjar_insercao(TipoHEAP *heap, int index);

void heap_inserir(TipoHEAP *heap, Registro elemento);

TipoRegistro remover_maior(TipoHEAP *heap);

int heapear_descendo(TipoHEAP *heap, int index);

#endif /* HEAP_BINARIO_H */