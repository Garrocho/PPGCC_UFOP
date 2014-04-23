#include <math.h>
#include "grafo.h"

int solucao_atual = 0;
int melhor_custo = INFINITO;
int maior_custo = 0;
int maior_id = 0;
int qtde_podas = 0;
No_Cidade_Ponteiro no_folha_de_melhor_caminho = NULL;

Graph *gr_load(const char * endereco) {
	FILE *arq;
	arq = fopen(endereco, "r");
	if (arq == NULL) {
		printf("Arquivo Invalido...\n");
		exit(EXIT_FAILURE);
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

void imprimir_rota(int a[], int k, Graph *graph){
    int j;
    for(j = 0; j <= k; j++){
        printf("-> %d ", a[j]);
    }

    printf("\n");
    int distancia_total = 0;
    for(j = 0; j < k; j++){
        int distancia = graph->matriz_adjacencia[ a[j] -1 ][ a[j+1] - 1];
        distancia_total += distancia;
    }
    
    printf("Custo Total: %d\n", distancia_total);
}

int distancia_total(int a[], int k, Graph *graph){
    int j;
    int distancia_total = 0;
    
    for(j = 0; j < k; j++){
        distancia_total += graph->matriz_adjacencia[ a[j] -1 ][ a[j+1] - 1];
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
        int distancia = graph->matriz_adjacencia[ a[j] -1 ][ a[j+1] - 1];
        
        if(distancia == INFINITO)
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
            int distancia = graph->matriz_adjacencia[ a[k-1] -1 ][j];
            
            if(distancia != INFINITO && (!vertice_na_solucao(a, k, j+1) || (k == graph->numero_vertices && (a[0] == j+1) ) ) ){ 
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
            printf("\nNova solucao Melhor: %d\n", solucao_atual);
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

void branch_bound(Graph *graph, No_Cidade_Ponteiro no_temporario)
{
    int i,pos_cidade, custo;
    No_Cidade_Ponteiro no;

    if (no_temporario->profundidade == graph->numero_vertices - 1)
    {
        if (no_temporario->custo + graph->matriz_adjacencia[no_temporario->id_cidade][0] < melhor_custo)
        {
            melhor_custo = no_temporario->custo + graph->matriz_adjacencia[no_temporario->id_cidade][0];
            printf("\nNova Solucao Melhor:\n");
            imprimir_caminho(no_temporario);
            printf("-> %d", maior_id+1);
            printf("\nCusto Total: %d\n", maior_custo+graph->matriz_adjacencia[maior_id][no_temporario->id_cidade]);
            maior_custo = 0;
        }
        free(no_temporario);
        return;
    }
    for (i=1;i<graph->numero_vertices;++i)
    {
        pos_cidade = (int) pow(2,i);
        if ((no_temporario->cidades_visitadas & pos_cidade) != 0)
            continue;

        custo = no_temporario->custo + graph->matriz_adjacencia[no_temporario->id_cidade][i];
        if (custo > melhor_custo) {
            if (custo < INFINITO) 
                qtde_podas++;
        }
        else {
            no = (No_Cidade_Ponteiro) malloc(sizeof(struct No_Cidade));
            no->id_cidade = i;
            no->cidades_visitadas = no_temporario->cidades_visitadas | pos_cidade;
            no->custo = custo;
            no->profundidade = no_temporario->profundidade +1;
            no->no_pai = no_temporario;
            branch_bound(graph, no);
        }
    }
    if (no_temporario) 
        free(no_temporario);
    return;   
}

void imprimir_caminho(No_Cidade_Ponteiro n)
{
    if (n->profundidade==0)
    {
        printf("%d ", n->id_cidade+1);
        if (maior_custo < n->custo) {
            maior_custo = n->custo;
        }
        maior_id = n->id_cidade;
        return;
    }
    imprimir_caminho(n->no_pai);
    printf("-> %d ", n->id_cidade+1);
    if (maior_custo < n->custo) {
        maior_custo = n->custo;
    }
    return;
}

int prim(Graph *graph, int inicio, int debug) {
    int distancias[graph->numero_vertices];
    int marcados[graph->numero_vertices];
    int caminho[graph->numero_vertices];
    int i, menor_distancia, cont_cam=0;

    for (i = 0; i < graph->numero_vertices; i++) {
        distancias[i] = INFINITO;
        marcados[i] = 0;
    }
    distancias[inicio] = 0;
   
    int corrente = inicio;
    int custo = 0;
    while (corrente != -1) {
        marcados[corrente]=1;
        custo += distancias[corrente];
        caminho[cont_cam++] = corrente;

        for (i = 0; i < graph->numero_vertices; i++)
            distancias[i] = INFINITO;
        distancias[corrente] = 0;
       
        for (i = 0; i < graph->numero_vertices; i++) {
            if (graph->matriz_adjacencia[corrente][i]) {
                if (distancias[i] > graph->matriz_adjacencia[corrente][i])
                    distancias[i] = graph->matriz_adjacencia[corrente][i];
            }
        }

        corrente=-1;
        menor_distancia = INFINITO;
        for (i = 0; i < graph->numero_vertices; i++) {
            if (!marcados[i] && distancias[i] < menor_distancia) {
                corrente = i;
                menor_distancia = distancias[i];
            }
        }
                 
    }
    if (debug) {
        printf("\n%d", caminho[0]+1);
        for (i = 1; i < cont_cam; i++) {
            printf(" -> %d", caminho[i]+1);
        }
        printf("\nTotal %d\n", custo);
    }
    if (cont_cam == graph->numero_vertices)
        return custo;
    else
        return INFINITO;
}

void iniciar_backtrack(Graph *graph) {
    int a[graph->numero_vertices+1], i;
    for(i = 0; i <= graph->numero_vertices; i++){
        a[i] = 0;
    }
    printf("\n#### Backtrack ####\n");
    backtrack(a, -1, graph);
}

void iniciar_prim(Graph *graph) {
    int menor=INFINITO, custo, menor_i, i;
    for(i = 0; i < graph->numero_vertices; i++){
        custo = prim(graph, i, 0);
        if (custo < menor) {
            menor_i = i;
            menor = custo;
        }
    }
    printf("\n\n#### Arvore Geradora Minima ####\nMenor Custo: %d", menor);
    prim(graph, menor_i, 1);
}

void iniciar_branch_bound(Graph *graph) {
    No_Cidade_Ponteiro no_inicial;
    no_inicial = (No_Cidade_Ponteiro) malloc(sizeof(struct No_Cidade));
    no_inicial->id_cidade =0;
    no_inicial->cidades_visitadas = 1;
    no_inicial->custo = 0;
    no_inicial->profundidade =0;
    no_inicial->no_pai =NULL;
    printf("\n\n#### Branch and Bound ####\n");
    branch_bound(graph, no_inicial);
    printf("\nQuantidade de Podas: %d\n", qtde_podas);
}