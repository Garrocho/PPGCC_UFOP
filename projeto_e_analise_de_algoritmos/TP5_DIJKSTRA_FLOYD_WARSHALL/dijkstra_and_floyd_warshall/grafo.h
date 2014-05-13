#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITO 9999999
#define MEMBRO 1
#define NAOMEMBRO 0

typedef struct graph {
    int numero_vertices;
    int** matriz_adjacencia;
}Graph;

Graph *gr_load(const char *endereco);

void gr_free(Graph *graph);

void inicia_dijkstra(Graph *graph, const char *caminho);

void dijkstra(Graph *graph, int origem, FILE *arquivo);

void inicia_floyd_warshall(Graph *graph, const char *caminho);

void floyd_warshall(Graph *graph, FILE *arquivo);

#endif