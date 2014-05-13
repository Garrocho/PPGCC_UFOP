#ifndef LISTA_H
#define LISTA_H

typedef struct {
    int chave;
    int peso;
}Item;

typedef struct No *ApontadorNo;

typedef struct No {
    Item Item;
    ApontadorNo Prox;
    ApontadorNo Ant;
}TipoNo;

typedef struct {
	int quantidade;
    ApontadorNo Primeiro;
    ApontadorNo Ultimo;
}TipoNodo;

typedef struct {
    int tamanho;
    TipoNodo *nodos;
}TipoLista;

TipoLista* cria_lista(int tamanho);

void add_item(TipoLista *lista, int origem, int destino, int peso);

int tem_item(TipoLista lista, int origem, int destino);

void imprime_lista(TipoLista lista);

void grava_lista(TipoLista lista, int tamanho, int densidade);

void apaga_lista(TipoLista *lista);

#endif /* LISTA_H */