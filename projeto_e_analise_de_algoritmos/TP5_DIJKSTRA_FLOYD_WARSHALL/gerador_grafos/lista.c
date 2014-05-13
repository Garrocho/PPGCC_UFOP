#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

TipoLista* cria_lista(int tamanho) {
    int i;
    TipoLista* lista = (TipoLista*)malloc(sizeof(TipoLista));
    lista->nodos = (TipoNodo*)malloc(sizeof(TipoNodo)*tamanho);
    lista->tamanho = tamanho;
    for (i=0; i<tamanho; i++) {
        lista->nodos[i].quantidade = 0;
        lista->nodos[i].Primeiro = (ApontadorNo) malloc(sizeof(TipoNo));
        lista->nodos[i].Primeiro->Prox = NULL;
        lista->nodos[i].Primeiro->Ant = NULL;
        lista->nodos[i].Ultimo = lista->nodos[i].Primeiro;
    }
    return lista;
}

void add_item(TipoLista *lista, int origem, int destino, int peso) {
    ApontadorNo aux;
    aux=lista->nodos[origem].Ultimo;
    lista->nodos[origem].quantidade++;
    lista->nodos[origem].Ultimo->Prox = (ApontadorNo) malloc(sizeof(TipoNo));
    lista->nodos[origem].Ultimo = lista->nodos[origem].Ultimo->Prox;
    lista->nodos[origem].Ultimo->Ant = aux;
    lista->nodos[origem].Ultimo->Item.chave = destino;
    lista->nodos[origem].Ultimo->Item.peso = peso;
    lista->nodos[origem].Ultimo->Prox= NULL;
}

int tem_item(TipoLista lista, int origem, int destino) {
    ApontadorNo aux;
    aux = lista.nodos[origem].Primeiro->Prox;
     while(aux != NULL) {
        if (aux->Item.chave == destino)
            return 1;
        aux = aux->Prox;
    }
    return 0;
}

void imprime_lista(TipoLista lista) {
    ApontadorNo aux;
    int i;

    for (i=0; i<lista.tamanho; i++) {
        aux = lista.nodos[i].Primeiro->Prox;
         while(aux != NULL) {
            printf("%d %d %d\n", i, aux->Item.chave, aux->Item.peso);
            aux = aux->Prox;
        }
    }
}

void grava_lista(TipoLista lista, int tamanho, int densidade) {
    ApontadorNo aux;
    char endereco[50];
    FILE *arquivo;
    int i;
    
    sprintf(endereco, "grafo_t%d_d%d.txt", tamanho, densidade);
    arquivo = fopen(endereco, "w");
    fprintf(arquivo, "%d\n", lista.tamanho);

    for (i=0; i<lista.tamanho; i++) {
        aux = lista.nodos[i].Primeiro->Prox;
         while(aux != NULL) {
            fprintf(arquivo, "%d %d %d\n", i+1, aux->Item.chave+1, aux->Item.peso+1);
            aux = aux->Prox;
        }
    }
    fclose(arquivo);
}

void apaga_lista(TipoLista *lista) {
    ApontadorNo aux1, aux2;
    int i;

    for (i=0; i<lista->tamanho; i++) {
        aux1 = lista->nodos[i].Ultimo;
        aux2 = aux1->Ant;
        while(aux2 != NULL){
            lista->nodos[i].Ultimo = aux2;
            aux2 = aux2->Ant;
            free(aux1);
            aux1 = lista->nodos[i].Ultimo;
        }
        free(aux1);
    }
    free(lista->nodos);
    free(lista);
}
