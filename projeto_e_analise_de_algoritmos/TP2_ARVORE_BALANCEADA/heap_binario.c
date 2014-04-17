#include <stdio.h>
#include <stdlib.h>
#include "heap_binario.h"

void inicializar_heap(TipoHEAP *h, int tamanho) {
    h->elementos = (Registro) malloc(sizeof(TipoRegistro)*(tamanho));
    h->tamanho = 0;
    h->tamanho_max = tamanho;
}

void destruir_heap(TipoHEAP * h) {
    free(h->elementos);
    h->tamanho = 0;
}

int heap_pai(int n) {
    return ((int) n/2);
}

int filho_esquerda(int n) {
    return 2*n;
}

int filho_direita(int n) {
    return 2*n + 1;
}

void heap_imprimir(TipoHEAP h) {
    int tamanho = h.tamanho;
    int i;
    for (i=0; i<tamanho; i++)
        printf("%s\t%d\n", h.elementos[i].palavra, h.elementos[i].qtde);
    printf("\n");
}

void heap_trocar(TipoHEAP *heap, int index, int index_to) {
    TipoRegistro temp = heap->elementos[index_to];
    heap->elementos[index_to] = heap->elementos[index];
    heap->elementos[index] = temp;
    return;
}

void heapear_subindo(TipoHEAP *heap, int index) {
    int pai = heap_pai(index);

    if (pai == -1)
        return;

    if (heap->elementos[index].qtde > heap->elementos[pai].qtde) {
        heap_trocar(heap, index, pai);
        heapear_subindo(heap, pai);
    }
    return;
}

void arranjar_insercao(TipoHEAP *heap, int index) {
    int i;
    for(i = index; i>=1; i--){
        heapear_subindo(heap, i);
    }
    return;
}

void heap_inserir(TipoHEAP *heap, Registro elemento) {
    if (heap->tamanho >= heap->tamanho_max)
        return;
    heap->elementos[heap->tamanho] = (*elemento);
    arranjar_insercao(heap, heap->tamanho++);
    return;
}

TipoRegistro remover_maior(TipoHEAP *heap) {
    TipoRegistro maior;

    if (heap->tamanho == 0)
        return maior;
    maior = heap->elementos[0];
    heap->elementos[0] = heap->elementos[--heap->tamanho];
    heapear_descendo(heap, 0);

    return maior;
}

int heapear_descendo(TipoHEAP *heap, int index) {
    int filho, i, maior_filho;

    maior_filho = index;
    filho = filho_esquerda(index);

    for (i=0; i<=1; i++) {
        if ((filho + i) <= heap->tamanho) {
            if (heap->elementos[filho + i].qtde > heap->elementos[maior_filho].qtde)
                maior_filho = filho + i;
        }
    }

    if (maior_filho != index) {
        heap_trocar(heap, index, maior_filho);
        heapear_descendo(heap, maior_filho);
    }
    return maior_filho;
}