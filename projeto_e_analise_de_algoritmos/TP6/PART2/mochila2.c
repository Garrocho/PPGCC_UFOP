#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "mochila.h"
#define max(a, b) (a > b ? a : b)
int K,N;

int top_down(int, int, int*, int*, int**, int**);

int bottom_up(int, int, int*, int*, int**, int**);

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
		FILE *arquivo2;
		FILE* fp = fopen(infile, "r");
		if (fp == NULL)
		{
			printf("Nao pode abrir %s.\n", infile);
			exit(EXIT_FAILURE);
		}

		int n, W;
		fscanf(fp, "%d", &n);
		fscanf(fp, "%d", &W);

		int vals[n], wts[n], **matrix, **picks;
		int i = 0, j = 0, index = 0;

		while (!feof (fp) && index < n) {
			fscanf(fp, "%d", &j);
			wts[index++] = j;
		}

		index = 0;
		while (!feof (fp) && index < n) {
			fscanf(fp, "%d", &i);
			vals[index++] = i;
		}

		matrix = (int**)calloc(n, sizeof(int*));
		picks = (int**)calloc(n, sizeof(int*));
		K = N = W;
		for (i=0; i < n; i++) {
			matrix[i] = (int*)calloc(wts[n-1]+1, sizeof(int));
			picks[i] = (int*)calloc(wts[n-1]+1, sizeof(int));
		}

		char endereco[100];
		sprintf(endereco, "%s.sol", infile);
		arquivo = fopen(endereco, "w");

		clock_t start = clock();
		fprintf(arquivo, "Top Down\nLucro Otimo = %d\n", top_down(n-1, wts[n-1], wts, vals, matrix, picks));
		clock_t end = clock();
		double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
		fprintf(arquivo, "Tempo Total da execucao: %.2f\n", cpuTime);
		fprintf(arquivo, "Quantidade de Selecionados: %d\n", count_picks(n-1, wts[n-1], wts, picks));
		fprintf(arquivo, "Selecionados:\n");
		print_picks(n-1, wts[n-1], wts, picks, arquivo);

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

int top_down(int index, int size, int *weights, int *values, int **matrix, int **picks) {
	int take, dontTake;

	take = dontTake = 0;

	if (matrix[index][size] != 0)
		return matrix[index][size];

	if (size < K) {
		picks[index][size] = -1;
		matrix[index][size] = 0;
		return 0;
	}

	if (index == 0) {
		if ((size - weights[index]) >= K) {
			picks[index][size] = 1;
			matrix[index][size] = values[0];
			return values[0];
		}
		else {
			picks[index][size] = -1;
			matrix[index][size] = 0;
			return 0;
		}
	}

	if ((size - weights[index]) >= K) {
		take = values[index] + top_down(index-1, weights[index], weights, values, matrix, picks);
	}

	dontTake = top_down(index-1, size, weights, values, matrix, picks);
	printf("size %d index %d take %d\n\n", size, index, take);
	printf("size %d index %d dont_take %d\n\n", size, index, dontTake);
	matrix[index][size] = max(take, dontTake);

	if (take > dontTake)
		picks[index][size]=1;
	else
		picks[index][size]=-1;

	return matrix[index][size];
}

int bottom_up(int nItems, int size, int *weights, int *values, int **matrix, int **picks) {
	int i,j;

	for (i=1; i <= nItems; i++) {
		for (j=0; j <= size; j++) {
			if (weights[i-1] <= j) {
				matrix[i][j] = max(matrix[i-1][j], values[i-1] + matrix[i-1][j-weights[i-1]]);
				if (values[i-1] + matrix[i-1][j-weights[i-1]] > matrix[i-1][j])
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
	return matrix[nItems][size];
}

int count_picks(int item, int size, int *weights, int **picks) {
	int count = 0;
	while (item >= 0 && size >= 0) {
		if (picks[item][size] == 1) {
			count++;
			item--;
			size -= weights[item];
		}
		else {
			item--;
		}
	}
	return count;
}

void print_picks(int item, int size, int *weights, int **picks, FILE *arquivo) {

	while (item >= 0 && size >= 0) {
		if (picks[item][size] == 1) {
			fprintf(arquivo, "%d\n", item);
			item--;
			size -= weights[item];
		}
		else {
			item--;
		}
	}
}