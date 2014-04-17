#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_avl.h"

Registro cria_registro()
{
	Registro auxRegistro;
	auxRegistro = (Registro)malloc(sizeof(TipoRegistro));
	auxRegistro->qtde = 0;
	return auxRegistro;
}

int FB(TipoNodoAVL *raiz)
{
  if (raiz == NULL)
    return 0;
 
  return altura(raiz->esq) - altura(raiz->dir);
}

int altura(TipoNodoAVL *raiz)
{
  int esq, dir;

  if (raiz == NULL)
    return 0;

  esq = altura(raiz->esq);
  dir = altura(raiz->dir);

  if ( esq > dir )
    return esq + 1;
  else
    return dir + 1;
}

void RSE(TipoNodoAVL **raiz)
{
  TipoNodoAVL *aux;
  aux = (*raiz)->dir;
  (*raiz)->dir = aux->esq;
  aux->esq = (*raiz);
  (*raiz) = aux;
}

void RSD(TipoNodoAVL **raiz)
{
  TipoNodoAVL *aux;
  aux = (*raiz)->esq;
  (*raiz)->esq = aux->dir;
  aux->dir = (*raiz);
  (*raiz) = aux;
}

int balanca_esquerda(TipoNodoAVL **raiz)
{
  int fbe = FB ( (*raiz)->esq );
  if ( fbe > 0 )
  {
    RSD(raiz);
    return 1;
  }
  else if (fbe < 0 )
  { /* Rotação Dupla Direita */
    RSE( &((*raiz)->esq) );
    RSD( raiz ); /* &(*raiz) */
    return 1;
  }
  return 0;
}

int balanca_direita(TipoNodoAVL **raiz)
{
  int fbd = FB( (*raiz)->dir);
  if ( fbd < 0 )
  {
    RSE (raiz);
    return 1;
  }
  else if (fbd > 0 )
  { /* Rotação Dupla Esquerda */
    RSD( &((*raiz)->dir) );
    RSE( raiz ); /* &(*raiz) */
    return 1;
  }
  return 0;
}

int balanceamento(TipoNodoAVL **raiz)
{
	int fb = FB(*raiz);
	if ( fb > 1)
		return balanca_esquerda(raiz);
	else if (fb < -1 )
		return balanca_direita(raiz);
	else
		return 0;
}

void insere_avl(TipoArvoreAVL *raiz, Registro novoElemento)
{
	if (*raiz == NULL)
	{
		*raiz = (TipoNodoAVL*)malloc(sizeof(TipoNodoAVL));
		(*raiz)->elemento = *novoElemento;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;
	}
	if ( strncmp((*raiz)->elemento.palavra, novoElemento->palavra, TAMANHO_PALAVRA) == 0)
		{
			(*raiz)->elemento.qtde++;
		}
		else if ( strncmp((*raiz)->elemento.palavra, novoElemento->palavra, TAMANHO_PALAVRA) > 0 )
		{
			insere_avl(&(*raiz)->esq,novoElemento);
			balanceamento(&(*raiz));
		}
		else if ( strncmp((*raiz)->elemento.palavra, novoElemento->palavra, TAMANHO_PALAVRA) < 0 )
		{
			insere_avl(&(*raiz)->dir,novoElemento);
			balanceamento(&(*raiz));
		}
}

int tamanho_avl(TipoNodoAVL **auxArvore)
{
    int esq, dir;

  	if ((*auxArvore) == NULL)
    	return 0;

	esq = tamanho_avl(&(*auxArvore)->esq);
	dir = tamanho_avl(&(*auxArvore)->dir);

	return (esq + dir)+1;
}

void destruir_avl(TipoNodoAVL **auxArvore)
{
  	if ((*auxArvore)) {
		destruir_avl(&(*auxArvore)->esq);
		destruir_avl(&(*auxArvore)->dir);
		free(*auxArvore);
	}
}

void cria_arquivo_avl(TipoArvoreAVL auxArvore, FILE *arquivoInvertido)
{
	int k;
	if (auxArvore) {
		cria_arquivo_avl(auxArvore->esq, arquivoInvertido);
		fprintf(arquivoInvertido, "PALAVRA: ");
		for (k = 0; k < TAMANHO_PALAVRA; k++) {
			fputc(auxArvore->elemento.palavra[k], arquivoInvertido);
		}
		fprintf(arquivoInvertido, "\tQtde: %d\n", auxArvore->elemento.qtde);
		cria_arquivo_avl(auxArvore->dir, arquivoInvertido);
	}
}