#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "arvore_avl.h"
#include "heap_binario.h"


void avl_para_heap(TipoNodoAVL *auxArvore, TipoHEAP *heap);


int main(int argc, char **argv) {

	if (argc == 1) {
		printf("ERRO: falta um parametro\n");
		exit(1);
	}

	clock_t start = clock();
    printf("Inserindo as palavras na árvore AVL...");  fflush(stdout);

	FILE *arquivoInvertido;
	FILE *arquivoTXT;

	char *arquivosTXT = argv[1];
	char *arquivosInvertido = "resultado.txt"; 
	int contPalavra;
	char letra;

	TipoArvoreAVL ArvoreAVL = NULL;
	Registro novoElementoAVL;

	novoElementoAVL = cria_registro();
	
	arquivoTXT = fopen(arquivosTXT, "r");
	rewind(arquivoTXT);

	do {
		letra = getc(arquivoTXT);
		for (contPalavra = 0; contPalavra <= TAMANHO_PALAVRA; contPalavra++)
			novoElementoAVL->palavra[contPalavra] = ' ';
		contPalavra = 0;

		while (letra != ' ' && letra != '\n' && letra != EOF)
		{
			if ( isalpha(letra) )
				novoElementoAVL->palavra[contPalavra++] = tolower(letra);
			letra = fgetc(arquivoTXT);
			if (contPalavra == TAMANHO_PALAVRA)
			{
				while(letra != ' ' && letra != '\n' && letra != EOF)
				{
					letra = fgetc(arquivoTXT);
				}
				contPalavra = 0;
			}
		}
		if (novoElementoAVL->palavra[0] != ' ')
			insere_avl(&ArvoreAVL, novoElementoAVL);
	} while (letra != EOF);

	printf("\nGravando as palavras da arvore e a quantidade de ocorrencias...");  fflush(stdout);
	arquivoInvertido = fopen(arquivosInvertido, "w");
	fprintf(arquivoInvertido, "PALAVRAS DA ARVORE AVL COM A QUANTIDADE DE OCORRENCIAS\n");
	cria_arquivo_avl(ArvoreAVL, arquivoInvertido);

	printf("\nInserindo elementos no heap binario...");  fflush(stdout);
	int tamanho = 0;
	tamanho = tamanho_avl(&ArvoreAVL);
    TipoHEAP meuHeap;
    inicializar_heap(&meuHeap, tamanho);
 	
 	avl_para_heap(ArvoreAVL, &meuHeap);
    TipoRegistro maior;
    int i, k;

    printf("\nGravando as 50 primeiras ocorrencias utilizando heap binario...");
    fprintf(arquivoInvertido, "\n50 PRIMEIRAS OCORRENCIAS UTILIZANDO O HEAP BINARIO\n");
    for (i=0; i < 50; i++) {
    	maior = remover_maior(&meuHeap);
    	for (k = 0; k < TAMANHO_PALAVRA; k++) {
			fputc(maior.palavra[k], arquivoInvertido);
		}
		fprintf(arquivoInvertido, "\tQtde: %d", maior.qtde);
		fputc('\n', arquivoInvertido);
    }
    destruir_avl(&ArvoreAVL);
    destruir_heap(&meuHeap);
    free(novoElementoAVL);
	fclose(arquivoTXT);
	fclose(arquivoInvertido);

    clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTerminado em %.3f.\n", cpuTime );  fflush(stdout);
    return 1;
}

void avl_para_heap(TipoNodoAVL *auxArvore, TipoHEAP *heap)
{
    if (auxArvore)
	{
		avl_para_heap(auxArvore->esq, heap);
		heap_inserir(heap, &auxArvore->elemento);
		avl_para_heap(auxArvore->dir, heap);
	}
}