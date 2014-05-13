#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void gerar_grafo(int tamanho, float densidade);

int main(int argc, char **argv) {

	if (argc == 1) {
		printf("Argumentos Inválidos...\nUtilize: ./a.out <tamanho_grafo>\n");
        exit(EXIT_FAILURE);
	}

	int tamanho = atoi(argv[1]);
	gerar_grafo(tamanho, 0.1);
	gerar_grafo(tamanho, 0.2);
	gerar_grafo(tamanho, 0.5);

	return EXIT_SUCCESS;
}

void gerar_grafo(int tamanho, float densidade) {
	int i, k, j, dest, peso, max_nodos, cont_max, max_atual;
	TipoLista* lista;
	lista = cria_lista(tamanho);
	max_nodos = (int)tamanho*densidade;

	for (i=0; i<tamanho; i++) {
		max_atual = max_nodos - lista->nodos[i].quantidade;
		for (k=0; k<max_atual; k++) {
			cont_max = 0;
			do {
				dest = rand()%tamanho;
				cont_max++;
				if (cont_max > tamanho)
					break;
			}while (tem_item(*lista, i, dest) || dest == i || lista->nodos[dest].quantidade == max_nodos);
			
			if (cont_max < tamanho) {
				peso = 10 + rand()%1000;
				add_item(lista, i, dest, peso);
				add_item(lista, dest, i, peso);
			}
			else {
				for (j=0; j<tamanho; j++) {
					if (!tem_item(*lista, i, j) && j != i && !(lista->nodos[j].quantidade == max_nodos)) {
						peso = 10 + rand()%1000;
						add_item(lista, i, j, peso);
						add_item(lista, j, i, peso);
						break;
					}
				}
			}
		}
	}
	grava_lista(*lista, lista->tamanho, max_nodos);
	apaga_lista(lista);
}
