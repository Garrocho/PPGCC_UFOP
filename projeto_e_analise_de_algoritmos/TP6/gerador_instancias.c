#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void gera_vetor(int, int);

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Argumentos Inválidos...\nUtilize: %s <tamanho_vetor> <distancia>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int tamanho = atoi(argv[1]);
	int distancia = atoi(argv[2]);

	gera_vetor(tamanho, distancia);

	return EXIT_SUCCESS;
}

void gera_vetor(int tamanho, int distancia) {
	char end[100];
	sprintf(end, "instancia_%d_%d.txt", tamanho, distancia);
	FILE *arquivo = fopen(end, "w");
	int i, aux=0;

	srand(time(NULL));
	fprintf(arquivo, "%d\n", tamanho);
	fprintf(arquivo, "%d\n", distancia*2);

	for (i=0; i<tamanho; i++) {
		aux += (1+(rand()%distancia));
		fprintf(arquivo, "%d\n", aux);
	}

	for (i=0; i<tamanho; i++)
		fprintf(arquivo, "%d\n", tamanho+(rand()%distancia));

	fclose(arquivo);
}