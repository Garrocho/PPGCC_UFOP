#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int* gera_vetor(int, int);

int solucao(int n, int k, int *distancias, int *lucros);

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Argumentos Inválidos...\nUtilize: %s <tamanho_vetor> <distancia>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int tamanho = atoi(argv[1]);
	int distancia = atoi(argv[2]);
	
	int* distancias = gera_vetor(tamanho, distancia);
	int* lucros = gera_vetor(tamanho, distancia);
	int lucro = solucao(tamanho, distancia/2, distancias, lucros);
	printf("%d\n", lucro);

	return EXIT_SUCCESS;
}

int solucao(int n, int k, int* distancias, int* lucros) {
	int i;
	int* solucao = (int*)malloc(sizeof(int)*n);

	for (i=0; i<n; i++) {
		solucao[i] = 0;
	}
	
	for (i=1; i<n-1; i++) {
		if ((distancias[i]-distancias[i-1]) >= k)
			solucao[i] = 1;
	}
}

int bottom_up(int n, int k, int size, int *distancias, int *lucros, int **matrix, int **picks) {
	int i, j;

	for (i=1; i <= n; i++) {
		for (j=0; j <= size; j++) {
			if (distancias[i-1] <= j) {
				matrix[i][j] = max(matrix[i-1][j], lucros[i-1] + matrix[i-1][j-distancias[i-1]]);

				if ((lucros[i-1] + matrix[i-1][j-distancias[i-1]] > matrix[i-1][j]) && 
					picks[i][j] = 1;
				else
					picks[i][j] = -1;
			}
			else {
				picks[i][j] = -1;
				matrix[i][j] = matrix[i-1][j];
			}
		}
	}
	return matrix[n][size];
}

int* gera_vetor(int tamanho, int distancia) {
	int i;
	int* vetor = (int*)malloc(sizeof(int)*tamanho);

	srand(time(NULL));

	vetor[0] = 1+(rand()%distancia);
	for (i=1; i<tamanho; i++) {
		vetor[i] = 1 + (rand()%distancia) + vetor[i-1];
	}
	return vetor;
}