#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#define TAMANHO_PALAVRA 30

typedef char TipoPalavra[TAMANHO_PALAVRA];

typedef struct
{
	TipoPalavra palavra;
	int qtde;
}TipoRegistro;

typedef TipoRegistro *Registro;

typedef struct NodoAVL
{
	TipoRegistro elemento;
	struct NodoAVL *esq, *dir;
}TipoNodoAVL;

typedef TipoNodoAVL *TipoArvoreAVL;

Registro cria_registro();

int FB(TipoNodoAVL *raiz);

int altura(TipoNodoAVL *raiz);

void RSE(TipoNodoAVL **raiz);

void RSD(TipoNodoAVL **raiz);

int balanca_esquerda(TipoNodoAVL **raiz);

int balanca_direita(TipoNodoAVL **raiz);

int balanceamento(TipoNodoAVL **raiz);

void insere_avl(TipoArvoreAVL *raiz, Registro novoElemento);

int tamanho_avl(TipoNodoAVL **auxArvore);

void cria_arquivo_avl(TipoArvoreAVL auxArvore, FILE *arquivoInvertido);

void destruir_avl(TipoNodoAVL **auxArvore);

#endif /* ARVORE_AVL_H */