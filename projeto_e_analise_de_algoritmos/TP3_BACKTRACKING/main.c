#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "back_tracking.h"	

int main(int argc, const char **argv) {

    if (argc < 2) {
        printf("Argumentos Inválidos...\nUtilize: ./a.out <entrada.txt>");
        exit(EXIT_FAILURE);
    }

    const char *endereco = argv[1];
    clock_t start = clock();

    Graph *graph = gr_load(endereco);
    int a[graph->numero_vertices+1];
    int i;
    for(i = 0; i <= graph->numero_vertices; i++){
        a[i] = 0;
    }
    backtrack(a, -1, graph);

    clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTempo total da execucao: %.2f\n", cpuTime);

    gr_free(graph);

    return EXIT_SUCCESS;
}