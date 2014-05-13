#include <stdio.h>
#include "grafo.h"

Graph *gr_load(const char * endereco) {
    FILE *arq;
    arq = fopen(endereco, "r");
    if (arq == NULL) {
        printf("Arquivo Invalido...\n");
        return NULL;
    }
    
    char tamanho_linha[100];
    char *linha;
    
    int nlinha = 0;
    
    linha = fgets(tamanho_linha, 100, arq);

    Graph *graph = malloc(sizeof(Graph));
    graph->numero_vertices = atoi(linha);
    
    graph->matriz_adjacencia = (int**)malloc(sizeof(int*) * graph->numero_vertices);
    
    int x, y;
    for(y=0; y < graph->numero_vertices; y++){
        graph->matriz_adjacencia[y] = malloc(sizeof(int) * graph->numero_vertices);
        
        for(x=0; x < graph->numero_vertices; x++){
            graph->matriz_adjacencia[y][x] = INFINITO;
        }
    }
    
    while (!feof(arq)) {
        linha = fgets(tamanho_linha, 100, arq);
        int vizinhos[3];
        int i = 0;
        char *valores = strtok(linha, " \n");

        while (valores != NULL) {
            vizinhos[i] = atoi(valores);
            valores = strtok(NULL, " \n");
            i++;
        }
        graph->matriz_adjacencia[vizinhos[0]-1][vizinhos[1]-1] = vizinhos[2];
        nlinha++;
    }
    fclose(arq);
    return graph;
}

void gr_free(Graph *graph){
    int y;
    for(y=0; y < graph->numero_vertices; y++){
        free(graph->matriz_adjacencia[y]);
    }
    
    free(graph->matriz_adjacencia);
    free(graph);
}

void inicia_dijkstra(Graph *graph, const char *caminho) {
    int i;
    FILE *arquivo;
    char endereco[50];
    sprintf(endereco, "%s_dijkstra.txt", caminho);
    arquivo = fopen(endereco, "w");
    for (i=0; i<graph->numero_vertices; i++) {
        dijkstra(graph, i, arquivo);
    }
    fclose(arquivo);
}

void dijkstra(Graph *graph, int origem, FILE *arquivo)
{
    int dist[graph->numero_vertices], perm[graph->numero_vertices], path[graph->numero_vertices];
    int corrente, i, k, dc, testados=0, aux=0;
    int menor_dist, nova_dist;
    
    for (i = 0; i < graph->numero_vertices; i++) {
        perm[i] = NAOMEMBRO;
        dist[i] = INFINITO;
    }

    origem = 0;

    perm[origem] = MEMBRO;
    dist[origem] = 0;
    
    corrente = origem;
    k = corrente;

    while (testados != (graph->numero_vertices-1))
    {
        menor_dist = INFINITO;
        dc = dist[corrente];

        for (i = 0; i < graph->numero_vertices; i++) 
        {
            if (perm[i] == NAOMEMBRO) 
            {
                if (graph->matriz_adjacencia[corrente][i] != INFINITO) 
                {
                    nova_dist = dc + graph->matriz_adjacencia[corrente][i];

                    if (nova_dist < dist[i]) 
                    {
                        dist[i] = nova_dist;
                        path[i] = corrente;
                    }
                }
                
                if (dist[i] < menor_dist) 
                {
                    menor_dist = dist[i];
                    k = i;
                }
            }
        } 
        corrente = k;
        perm[corrente] = MEMBRO;
        aux += dist[corrente];  
        testados++;          
    }
    for (i=1; i <graph->numero_vertices; i++) {
        int caminho = i;
        fprintf(arquivo, "Origem: %d\tDestino: %d", origem+1, caminho+1);
        fprintf(arquivo, "\tCusto: %d", dist[caminho]);
        fprintf(arquivo, "\tCaminho: ");
        fprintf(arquivo, "%d <- ", caminho+1);
        while (caminho != origem)
        {
            fprintf(arquivo, "%d", path[caminho]+1);
            caminho = path[caminho];
            if (caminho != origem)
                fprintf(arquivo, " <- ");
        }
        fprintf(arquivo, "\n");
    }
}

void inicia_floyd_warshall(Graph *graph, const char *caminho) {
    FILE *arquivo;
    char endereco[50];
    sprintf(endereco, "%s_floyd_warshall.txt", caminho);
    arquivo = fopen(endereco, "w");
    floyd_warshall(graph, arquivo);
    fclose(arquivo);
}

void floyd_warshall(Graph *graph, FILE *arquivo) {
    int k, i, j, **caminho;

    caminho = (int**)malloc(sizeof(int*) * graph->numero_vertices);
    
    for(i=0; i < graph->numero_vertices; i++){
        caminho[i] = malloc(sizeof(int) * graph->numero_vertices);
        
        for(k=0; k < graph->numero_vertices; k++){
            caminho[i][k] = k;
        }
    }

    for (k = 0; k < graph->numero_vertices; k++)
        for (i = 0; i < graph->numero_vertices; i++)
            for (j = 0; j < graph->numero_vertices; j++)
                if (i != j && graph->matriz_adjacencia[i][k] != INFINITO && graph->matriz_adjacencia[k][j] != INFINITO)
                    if ((graph->matriz_adjacencia[i][k] + graph->matriz_adjacencia[k][j]) < graph->matriz_adjacencia[i][j]) 
                    {
                        graph->matriz_adjacencia[i][j] = graph->matriz_adjacencia[i][k] + graph->matriz_adjacencia[k][j];
                        caminho[i][j] = caminho[i][k];
                    }

    for(i=0; i < graph->numero_vertices; i++){
        for(k=0; k < graph->numero_vertices; k++) {
            if (k!=i) {
                fprintf(arquivo, "Origem: %d\tDestino: %d\tCusto: %d\tCaminho: ", i+1, k+1, graph->matriz_adjacencia[i][k]);
                int origem = k;

                do {
                    fprintf(arquivo, "%d <- ", origem+1);
                    origem = caminho[origem][i];
                }while(origem != i && origem != INFINITO);
                fprintf(arquivo, "%d\n", i+1);
            }
        }
    }
    for(k=0; k < graph->numero_vertices; k++){
        free(caminho[k]);
    }
    free(caminho);
}