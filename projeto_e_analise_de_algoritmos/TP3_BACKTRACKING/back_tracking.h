#ifndef BACK_TRACKING_H
#define BACK_TRACKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
	int numero_vertices;
	int** matriz_adjacencia;
}Graph;

Graph *gr_load(const char *endereco);

void gr_free(Graph *graph);

int distancia_total(int a[], int k, Graph *graph);

int vertice_na_solucao(int a[], int k, int vertice);

void imprimir_rota(int a[], int k, Graph *graph);

int verifica_solucao(int a[], int k, Graph *graph);

int is_solution(int a[], int k, Graph *graph);

void construct_candidate(int a[], int k, Graph *graph, int c[], int *ncandidatos);

void undo_move(int a[], int k, Graph *graph);  

void backtrack(int a[], int k, Graph *graph);

#endif