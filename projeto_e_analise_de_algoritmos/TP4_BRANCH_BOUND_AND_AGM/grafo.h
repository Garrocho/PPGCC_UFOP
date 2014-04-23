#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITO 1000000

typedef struct graph {
	int numero_vertices;
	int** matriz_adjacencia;
}Graph;

typedef struct No_Cidade *No_Cidade_Ponteiro;

struct No_Cidade{
  int id_cidade;
  int cidades_visitadas;
  int profundidade;
  No_Cidade_Ponteiro no_pai;
  int custo;
};

Graph *gr_load(const char *endereco);

void gr_free(Graph *graph);

int distancia_total(int a[], int k, Graph *graph);

int vertice_na_solucao(int a[], int k, int vertice);

void imprimir_rota(int a[], int k, Graph *graph);

void imprimir_matriz(Graph *graph);

int verifica_solucao(int a[], int k, Graph *graph);

int is_solution(int a[], int k, Graph *graph);

void construct_candidate(int a[], int k, Graph *graph, int c[], int *ncandidatos);

void undo_move(int a[], int k, Graph *graph);  

void backtrack(int a[], int k, Graph *graph);

int prim(Graph *graph, int inicio, int debug);

void branch_bound(Graph *graph, No_Cidade_Ponteiro no_temporario);

void imprimir_caminho(No_Cidade_Ponteiro n);

void iniciar_backtrack(Graph *graph);

void iniciar_prim(Graph *graph);

void iniciar_branch_bound(Graph *graph);

#endif