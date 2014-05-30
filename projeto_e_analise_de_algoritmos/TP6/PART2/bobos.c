#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (a > b ? a : b)
int K;

int top_down(int, int, int *, int *, int **, int **, int);

int count_picks(int, int, int *, int **);

void print_picks(int, int, int*, int**, FILE*);

int main(int argc, const char * argv[])
{
	if (argc != 2) {
		printf("Uso: ./a.out <arquivos>\n");
		exit(EXIT_FAILURE);
	}

	else {
		const char* infile = argv[1];
		FILE *arquivo;
		FILE* fp = fopen(infile, "r");

		if (fp == NULL)
		{
			printf("Nao pode abrir %s.\n", infile);
			exit(EXIT_FAILURE);
		}

		int n;
		fscanf(fp, "%d", &n);
		fscanf(fp, "%d", &K);

		int vals[n], wts[n], **matrix, **picks;
		int i = 0, j = 0, indice = 0;

		while (!feof (fp) && indice < n) {
			fscanf(fp, "%d", &j);
			wts[indice++] = j;
		}

		indice = 0;
		while (!feof (fp) && indice < n) {
			fscanf(fp, "%d", &i);
			vals[indice++] = i;
		}

		matrix = (int**)calloc(n, sizeof(int*));
		picks = (int**)calloc(n, sizeof(int*));

		for (i=0; i < n; i++) {
			matrix[i] = (int*)calloc(wts[n-1]+K+1, sizeof(int));
			picks[i] = (int*)calloc(wts[n-1]+K+1, sizeof(int));
		}

		char endereco[100];
		sprintf(endereco, "%s.sol", infile);
		arquivo = fopen(endereco, "w");

		clock_t start = clock();
		fprintf(arquivo, "Top Down\nLucro Otimo = %d\n", top_down(n-1, wts[n-1]+K, wts, vals, matrix, picks, 0));
		clock_t end = clock();
		double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
		fprintf(arquivo, "Tempo Total da execucao: %.2f\n", cpuTime);
		fprintf(arquivo, "Quantidade de Selecionados: %d\n", count_picks(n-1, wts[n-1]+K, wts, picks));
		fprintf(arquivo, "Selecionados:\n");
		print_picks(n-1, wts[n-1]+K, wts, picks, arquivo);

		fclose(fp);
		fclose(arquivo);

		for (i=0; i < n; i++) {
			free(matrix[i]);
			free(picks[i]);
		}

		free(matrix);
		free(picks);
	}
	return EXIT_SUCCESS;
}

int top_down(int indice, int size, int *dists, int *lucros, int **matriz, int **escolhidos, int ul_dist_sel) {
	int tomar, nao_tomar;
	tomar = nao_tomar = 0;

	if (matriz[indice][size] != 0)
		return matriz[indice][size];

	if (indice == 0 || size < K) {
		if ((size - dists[indice]) >= K) {
			escolhidos[indice][size] = 1;
			matriz[indice][size] = lucros[0];
			return lucros[0];
		}
		else {
			escolhidos[indice][size] = -1;
			matriz[indice][size] = 0;
			return 0;
		}
	}

	if ((ul_dist_sel == 0) || (size - dists[indice]) >= K) 
		tomar = lucros[indice] + top_down(indice-1, dists[indice], dists, lucros, matriz, escolhidos, dists[indice]);
	
	nao_tomar = top_down(indice-1, size, dists, lucros, matriz, escolhidos, ul_dist_sel);
	matriz[indice][size] = max(tomar, nao_tomar);

	if (tomar > nao_tomar)
		escolhidos[indice][size]=1;
	else
		escolhidos[indice][size]=-1;
	return matriz[indice][size];
}

int count_picks(int item, int size, int *weights, int **picks) {
	int count = 0;
	while (item >= 0) {
		if (picks[item][size] == 1) {
			count++;
			size = weights[item];
			item--;
		}
		else {
			item--;
		}
	}
	return count;
}

void print_picks(int item, int size, int *weights, int **picks, FILE *arquivo) {

	while (item >= 0) {
		if (picks[item][size] == 1) {
			fprintf(arquivo, "%d\n", item);
			size = weights[item];
			item--;
		}
		else {
			item--;
		}
	}
}