#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "back_tracking.h"

void prim(Graph *graph);

int main(int argc, const char **argv) {

    if (argc < 2) {
        printf("Argumentos Inválidos...\nUtilize: ./a.out <entrada.txt>");
        exit(EXIT_FAILURE);
    }

    const char *endereco = argv[1];
    clock_t start = clock();

    Graph *graph = gr_load(endereco);
    imprimir_matriz(graph);
    int i;
    for(i = 0; i < graph->numero_vertices; i++){
       quick_sort(graph->matriz_adjacencia[i], 0, graph->numero_vertices - 1);
    }
    imprimir_matriz(graph);

    prim(graph);

    clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTempo total da execucao: %.2f\n", cpuTime);

    gr_free(graph);

    return EXIT_SUCCESS;
}

/*void prim(Graph *graph) {
    int i, k, menor_distancia, cont_proc =0;
    int custo = 0;
    int posicao_atual = 0;
    int cont_lista = 0;
    int processar[graph->numero_vertices];
    Aresta aresta;
    Aresta *lista = (Aresta*)malloc(sizeof(Aresta)*graph->numero_vertices);

    aresta = graph->matriz_adjacencia[0][0];
    for(i=1; i<graph->numero_vertices; i++) {
        if (graph->matriz_adjacencia[i][0].distancia < aresta.distancia) {
            aresta = graph->matriz_adjacencia[i][0];
        }
    }
    lista[cont_lista++] = aresta;
    printf("svertice %d dvertice %d distancia %d\n", aresta.svertice, aresta.dvertice, aresta.distancia);

    while(cont_lista < graph->numero_vertices) {
        
        for (k=0; k < cont_lista; k++) {
            menor_distancia = INFINITO;
            //ok = 1
            for(i=0; i<graph->numero_vertices; i++) {
                printf("lista S: %d D: %d\n", lista[k].svertice, lista[k].dvertice);
                //printf("Analisando pos %d menor_distancia %d\n", i, menor_distancia);
                if (lista[k].svertice == graph->matriz_adjacencia[lista[k].svertice-1][i].svertice && lista[k].dvertice != graph->matriz_adjacencia[lista[k].svertice-1][i].dvertice) {
                    processar[cont_proc++] = graph->matriz_adjacencia[lista[k].svertice-1][i].svertice-1;
                }
            }
        }

        for (i=0; i < cont_proc; i++) {
            printf("processar S: %d D: %d D: %d\n", graph->matriz_adjacencia[lista[k].svertice-1][i].svertice, graph->matriz_adjacencia[lista[k].svertice-1][i].dvertice, graph->matriz_adjacencia[lista[k].svertice-1][i].distancia);
        }

        printf("saindo\n");
        lista[cont_lista++] = aresta;
        break;
    }

    for (i=0; i < cont_lista; i++)
        printf("s %d d %d Distancia %d\n", lista[i].svertice, lista[i].dvertice, lista[i].distancia);

}*/

void prim(Graph *graph) {
    int i,j;            /* counters */
    int intree[graph->numero_vertices];      /* is the vertex in the tree yet? */
    int distance[graph->numero_vertices];     /* distance vertex is from start */
    int v;              /* current vertex to process */
    int w;              /* candidate next vertex */
    int distancia;         /* edge weight */
    int dist;           /* best current distance from start */
    int parent[graph->numero_vertices];

    for (i=1; i<=graph->numero_vertices; i++) {
        intree[i] = 0;
        distance[i] = INFINITO;
        parent[i] = -1;
    }

    distance[0] = 0;
    v = 0;

    while (intree[v] == 0) {
        intree[v] = 1;
        for (i=0; i<graph->numero_vertices; i++) {
            w = graph->matriz_adjacencia[v][i].dvertice;
            distancia = graph->matriz_adjacencia[v][i].distancia;
            if ((distance[w] > distancia) && (intree[w] == 0)) {
                distance[w] = distancia;
                parent[w] = v;
            }
        }

        v = 1;
        dist = INFINITO;
        for (i=1; i<=graph->numero_vertices; i++) 
            if ((intree[i] == 0) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
    }

    for (i=1; i<=graph->numero_vertices; i++) {
        printf(" %d parent=%d\n",i,parent[i]);
    }
}


/*
if (graph->matriz_adjacencia[lista[k].svertice-1][i].svertice != lista[k].svertice && graph->matriz_adjacencia[lista[k].svertice-1][i].dvertice != lista[k].dvertice) {
                    printf("Processando %d\n", graph->matriz_adjacencia[lista[k].svertice-1][i].dvertice-1);
                    if (graph->matriz_adjacencia[lista[k].svertice-1][i].distancia < menor_distancia) {
                        aresta = graph->matriz_adjacencia[lista[k].svertice-1][i];
                        menor_distancia = aresta.distancia;
                        printf("Menor Distancia %d\n", aresta.distancia);
                    }
                }*/



/*int prim(Graph *graph) {
    int fixo[graph->numero_vertices];
    int custo[graph->numero_vertices];
    int total = 0, i, faltam, no;

    for(i=0; i<graph->numero_vertices; i++) {
        fixo[i] = 0;
        custo[i] = INFINITO;
    }
    custo[0] = 0;

    for(faltam = graph->numero_vertices; faltam>0; faltam--) {
        no = -1;
        for(i=0; i<graph->numero_vertices; i++)
            if(!fixo[i] && (no==-1 || custo[i] < custo[no]))
                no = i;
        fixo[no] = 1;

        if(custo[no] == INFINITO) {
            total = INFINITO;
            break;
        }
        total += custo[no];

        for(i=0; i<graph->numero_vertices; i++)
            if(custo[i] > graph->matriz_adjacencia[no][i].distancia)
                custo[i] = graph->matriz_adjacencia[no][i].distancia;
    }
    for(i=0; i<graph->numero_vertices; i++)
        printf("%d - ", custo[i]);
    printf("\nTotal: %d", total);
}*/

/*int prim(Graph *graph) {
    int distancias[graph->numero_vertices];
    int marcados[graph->numero_vertices];
    int caminho[graph->numero_vertices];
    int** renegados = (int**)malloc(sizeof(int*) * graph->numero_vertices);
    int posicao_atual = 0;
    int custo = 0;
    int menor_distancia, i, posicao_anterior, cont_caminho=0;

    int x, y;
    for(y=0; y < graph->numero_vertices; y++){
        renegados[y] = malloc(sizeof(int) * graph->numero_vertices);
        
        for(x=0; x < graph->numero_vertices; x++){
            renegados[y][x] = 0;
        }
    }

    for (i = 0; i < graph->numero_vertices; i++) {
        distancias[i] = INFINITO;
        marcados[i]=0;
    }
    distancias[0] = 0;
    marcados[0] = 1;
    caminho[cont_caminho++] = 0;
      
    while (posicao_atual != -1) {
        
        for (i = 0; i < graph->numero_vertices; i++) {
            distancias[i] = INFINITO;
            if (graph->matriz_adjacencia[posicao_atual][i].distancia != 0 && graph->matriz_adjacencia[posicao_atual][i].distancia < distancias[i]) {
                distancias[i] = graph->matriz_adjacencia[posicao_atual][i].distancia;
            }
        }
        posicao_anterior = posicao_atual;
        posicao_atual=-1;
        menor_distancia = INFINITO;

        for (i = 0; i < graph->numero_vertices; i++) {
            if (!marcados[i] && !renegados[posicao_anterior][i] && distancias[i] < menor_distancia) {
                posicao_atual = i;
                menor_distancia = distancias[i];
                printf("Vertice %d distancia %d menor distancia %d\n", i+1, distancias[i], menor_distancia);
            }
        }
        if (posicao_atual != -1) {
            caminho[cont_caminho++] = posicao_atual;
            marcados[posicao_atual]=1;
            custo += distancias[posicao_atual];
            printf("\nposicao_anterior: %d\n", caminho[cont_caminho-2]+1);
            printf("posicao_atual: %d\n", caminho[cont_caminho-1]+1);
            printf("Custo Atual: %d\n", custo);
            printf("Caminho: ");
            for (i=0; i<cont_caminho; i++)
                printf("%d -> ", caminho[i]+1);
            }
            printf("\n");
        if (posicao_atual == -1 && cont_caminho < graph->numero_vertices) {
            if (cont_caminho == 2) {
                printf("entrei\n");
                posicao_atual = 0;
                custo = 0;
                caminho[cont_caminho++] = 0;
                renegados[caminho[cont_caminho-2]][caminho[cont_caminho-1]] = 1;
                renegados[caminho[cont_caminho-2]][caminho[cont_caminho-1]] = 1;
                marcados[caminho[cont_caminho-1]]=0;
                break;
            }
            else if (cont_caminho > 2){
                printf("posicao_atual %d posicao_anterior %d cont_caminho %d\n", caminho[cont_caminho-1]+1, caminho[cont_caminho-2]+1, caminho[cont_caminho-2]+1 );
                posicao_atual = caminho[cont_caminho-2];
                marcados[caminho[cont_caminho-1]]=0;
                renegados[caminho[cont_caminho-2]][caminho[cont_caminho-1]] = 1;
                cont_caminho = cont_caminho-1;
                custo -= graph->matriz_adjacencia[caminho[cont_caminho-2]][caminho[cont_caminho-1]].distancia;
            }
        }
    }
    return custo;
}*/