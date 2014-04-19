#include "back_tracking.h"

int solucao_atual = 0;

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
    
    graph->matriz_adjacencia = (Aresta**)malloc(sizeof(Aresta*) * graph->numero_vertices);
    
    int x, y;
    for(y=0; y < graph->numero_vertices; y++){
        graph->matriz_adjacencia[y] = malloc(sizeof(Aresta) * graph->numero_vertices);
        
        for(x=0; x < graph->numero_vertices; x++){
            graph->matriz_adjacencia[y][x].svertice = INFINITO;
            graph->matriz_adjacencia[y][x].dvertice = INFINITO;
            graph->matriz_adjacencia[y][x].distancia = INFINITO;
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
        graph->matriz_adjacencia[vizinhos[0]-1][vizinhos[1]-1].svertice = vizinhos[0];
        graph->matriz_adjacencia[vizinhos[0]-1][vizinhos[1]-1].dvertice = vizinhos[1];
        graph->matriz_adjacencia[vizinhos[0]-1][vizinhos[1]-1].distancia = vizinhos[2];
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

void imprimir_rota(int a[], int k, Graph *graph){
    int j;
    printf("\nImprimindo Rota para %d elementos:\n", k);

    for(j = 0; j <= k; j++){
        printf("-> %d ", a[j]);
    }

    printf("\n");
    int distancia_total = 0;
    for(j = 0; j < k; j++){
        int distancia = graph->matriz_adjacencia[ a[j] -1 ][ a[j+1] - 1].distancia;
        distancia_total += distancia;
    }
    
    printf("Distancia percorrida: %d \n\n", distancia_total);
}

void imprimir_matriz(Graph *graph){

    printf("\nImprimir matriz\n");

    int x = 0, y = 0;
    printf("\t| ");

    for(x=0; x < graph->numero_vertices; x++){
        printf("%d\t", x + 1);
    }
    
    printf("\n");
    for(x=0; x < graph->numero_vertices; x++){
        printf("--------");
    }
    printf("\n");

    for(y=0; y < graph->numero_vertices; y++){
        printf("%d\t| ", y+1);
        for(x=0; x < graph->numero_vertices; x++){
            int distancia = graph->matriz_adjacencia[x][y].distancia;
            if(distancia != INFINITO){
                printf("%d\t", distancia);
            }
            else{
                printf(" - \t");
            }
        }
        printf("\n\n");
    }     
}

int distancia_total(int a[], int k, Graph *graph){
    int j;
    int distancia_total = 0;
    
    for(j = 0; j < k; j++){
        distancia_total += graph->matriz_adjacencia[ a[j] -1 ][ a[j+1] - 1].distancia;
    }
    return distancia_total;
}

int vertice_na_solucao(int a[], int k, int vertice){
    int i;
    for(i = 0; i < k; i++){
        if(a[i] == vertice){
            return 1;
        }  
    }    
    return 0;
}

int verifica_solucao(int a[], int k, Graph *graph){
    int j;
    for(j = 0; j < k; j++){
        if(vertice_na_solucao(a, k, j+1) && (k != graph->numero_vertices ) ){
            return 0;
        }
    }

    for(j = 0; j < k; j++){
        int distancia = graph->matriz_adjacencia[ a[j] -1 ][ a[j+1] - 1].distancia;
        
        if(distancia == 0)
            return 0;
    }
    return 1;
}

int is_solution(int a[], int k, Graph *graph){
    if(k < graph->numero_vertices){
        return 0;
    }
    if( k == graph->numero_vertices && ( a[0] != a[k]) ){
        return 0;
    }
    return verifica_solucao(a, k, graph);
}

void undo_move(int a[], int k, Graph *graph){
    int j;
    for(j = k; j <= graph->numero_vertices; j++){
        a[j] = 0;
    }
}

void construct_candidate(int a[], int k, Graph *graph, int c[], int *ncandidatos){
    int j;
    if(k == 0){
        *ncandidatos = graph->numero_vertices;
        
        for(j = 0; j < graph->numero_vertices; j++){
            c[j] = j+1;
        }
    }
    else{
        int i = 0;
        for(j = 0; j < graph->numero_vertices; j++){
            int distancia = graph->matriz_adjacencia[ a[k-1] -1 ][j].distancia;
            
            if(distancia != 0 && (!vertice_na_solucao(a, k, j+1) || (k == graph->numero_vertices && (a[0] == j+1) ) ) ){ 
                c[i] = j+1;
                i++;
            }
        }        
        *ncandidatos = i;
    }
}

void backtrack(int a[], int k, Graph *graph){     
	int ncandidatos, i, c[graph->numero_vertices];
	if ( is_solution(a, k, graph) ){
        
        int solucao_encontrada = distancia_total(a, k, graph);
        
        if(solucao_atual == 0 || solucao_atual > solucao_encontrada){
            solucao_atual = solucao_encontrada;
            printf("\nNova solucao: %d\n", solucao_atual);
            imprimir_rota(a, k, graph);
        }
        return;
	}
	else {
		k=k+1;

        if(k > (graph->numero_vertices +1)) {
             return;
        }
    	construct_candidate(a, k, graph, c, &ncandidatos);
    	
    	for ( i=0; i < ncandidatos; i++){
    		a[k] = c[i];
    		backtrack(a, k, graph);
            undo_move(a, k, graph);
    	}
	}
}

void quick_sort(Aresta *aresta, int left, int right) {
    int i, j, x;
    Aresta aux;
     
    i = left;
    j = right;
    x = aresta[(left + right) / 2].distancia;
     
    while(i <= j) {
        while(aresta[i].distancia < x && i < right) {
            i++;
        }
        while(aresta[j].distancia > x && j > left) {
            j--;
        }
        if(i <= j) {
            aux = aresta[i];
            aresta[i] = aresta[j];
            aresta[j] = aux;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(aresta, left, j);
    }
    if(i < right) {
        quick_sort(aresta, i, right);
    }
}