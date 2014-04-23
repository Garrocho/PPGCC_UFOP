#include <stdio.h>
#include <time.h>

#include "grafo.h"

int main(int argc, const char **argv) {

    if (argc < 2) {
        printf("Argumentos Inválidos...\nUtilize: ./a.out <entrada.txt>");
        exit(EXIT_FAILURE);
    }

    const char *endereco = argv[1];
    clock_t start = clock();

    Graph *graph = gr_load(endereco);
    
    iniciar_backtrack(graph);
    iniciar_prim(graph);
    iniciar_branch_bound(graph);

    clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo total da execucao: %.2f\n", cpuTime);

    gr_free(graph);

    return EXIT_SUCCESS;
}