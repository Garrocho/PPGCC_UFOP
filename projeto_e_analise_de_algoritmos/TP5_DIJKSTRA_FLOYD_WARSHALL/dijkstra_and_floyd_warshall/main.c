#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"	

int main(int argc, const char **argv) {

    if (argc < 2) {
        printf("Argumentos Inválidos...\nUtilize: ./a.out <entrada.txt>\n");
        exit(EXIT_FAILURE);
    }

    const char *endereco = argv[1];
    clock_t start = clock();

    Graph *graph = gr_load(endereco);

    inicia_dijkstra(graph, endereco);
    inicia_floyd_warshall(graph, endereco);

	clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTempo total da execucao: %.2f\n", cpuTime);

    gr_free(graph);

    return EXIT_SUCCESS;
}
