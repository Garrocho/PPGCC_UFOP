#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

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

		matrix = (int**)calloc(n, sizeof(int*));
		picks = (int**)calloc(n, sizeof(int*));

		for (i=0; i < n; i++) {
			matrix[i] = (int*)calloc(W+1, sizeof(int));
			picks[i] = (int*)calloc(W+1, sizeof(int));
		}

		while (!feof (fp) && index < n) {
			fscanf(fp, "%d", &j);
			wts[index++] = j;
		}

		index = 0;
		while (!feof (fp) && index < n) {
			fscanf(fp, "%d", &i);
			vals[index++] = i;
		}

		char endereco[100];
		sprintf(endereco, "%s.sol.top_down", infile);
		arquivo = fopen(endereco, "w");

		clock_t start = clock();
		fprintf(arquivo, "Top Down\nLucro Otimo = %d\n", top_down(n-1, W, wts, vals, matrix, picks));
		clock_t end = clock();
		double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
		fprintf(arquivo, "Tempo Total da execucao: %.2f\n", cpuTime);
		fprintf(arquivo, "Quantidade de Selecionados: %d\n", count_picks(n-1, W, wts, picks));
		fprintf(arquivo, "Selecionados:\n");
		print_picks(n-1, W, wts, picks, arquivo);

		for (i=0; i < n; i++) {
			for (j=0; j <= W; j++) {
				matrix[i][j] = 0;
				picks[i][j] = 0;
			}
		}

		char endereco2[100];
		sprintf(endereco2, "%s.sol.bottom_up", infile);
		arquivo2 = fopen(endereco2, "w");
		
		start = clock();
		fprintf(arquivo2, "Bottom Up\nLucro Otimo = %d\n", bottom_up(n-1, W, wts, vals, matrix, picks));
		end = clock();
		cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
		fprintf(arquivo2, "Tempo Total da execucao: %.2f\n", cpuTime);
		fprintf(arquivo2, "Quantidade de Selecionados: %d\n", count_picks(n-1, W, wts, picks));
		fprintf(arquivo2, "Selecionados:\n");
		print_picks(n-1, W, wts, picks, arquivo2);

		fclose(fp);
		fclose(arquivo);
		fclose(arquivo2);

		for (i=0; i < n; i++) {
			free(matrix[i]);
			free(picks[i]);
		}
		free(matrix);
		free(picks);
	}
	return EXIT_SUCCESS;
}