#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (a > b ? a : b)
int K;

int top_down(int indice, int *dists, int *lucros, int *vetor, int *escolhidos, int u);

int count_picks(int item, int *picks);

void print_picks(int item, int *picks, FILE *arquivo);

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

		int vals[n], wts[n], *vetor, *picks;
		int i = 0, j = 0, indice = 0;

		vetor = (int*)calloc(n, sizeof(int));
		picks = (int*)calloc(n, sizeof(int));

		while (!feof (fp) && indice < n) {
			fscanf(fp, "%d", &j);
			wts[indice++] = j;
		}

		indice = 0;
		while (!feof (fp) && indice < n) {
			fscanf(fp, "%d", &i);
			vals[indice++] = i;
		}

		char endereco[100];
		sprintf(endereco, "%s.sol", infile);
		arquivo = fopen(endereco, "w");

		clock_t start = clock();
		fprintf(arquivo, "Top Down\nLucro Otimo = %d\n", top_down(n-1, wts, vals, vetor, picks, 0));
		clock_t end = clock();
		double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
		fprintf(arquivo, "Tempo Total da execucao: %.2f\n", cpuTime);
		fprintf(arquivo, "Quantidade de Selecionados: %d\n", count_picks(n-1, picks));
		fprintf(arquivo, "Selecionados:\n");
		print_picks(n-1, picks, arquivo);

		fclose(fp);
		fclose(arquivo);

		free(vetor);
		free(picks);
	}
	return EXIT_SUCCESS;
}

int top_down(int indice, int *dists, int *lucros, int *vetor, int *escolhidos, int u) {
	int tomar, nao_tomar;
	tomar = nao_tomar = 0;

	if (vetor[indice] != 0)
		return vetor[indice];

	if (indice == 0) {
		if ((u - dists[indice]) >= K) {
			escolhidos[indice] = 1;
			vetor[indice] = lucros[0];
			return lucros[0];
		}
		return 0;
	}

	if ((u == 0) || (u - dists[indice]) >= K) 
		tomar = lucros[indice] + top_down(indice-1, dists, lucros, vetor, escolhidos, dists[indice]);
	
	nao_tomar = top_down(indice-1, dists, lucros, vetor, escolhidos, u);
	vetor[indice] = max(tomar, nao_tomar);

	if (tomar > nao_tomar)
		escolhidos[indice]=1;
	else
		escolhidos[indice]=-1;
	return vetor[indice];
}

int count_picks(int item, int *picks) {
	int count = 0;
	while (item >= 0) {
		if (picks[item] == 1) {
			item--;
			count++;
		}
		else {
			item--;
		}
	}
	return count;
}

void print_picks(int item, int *picks, FILE *arquivo) {

	while (item >= 0) {
		if (picks[item] == 1) {
			fprintf(arquivo, "%d\n", item);
			item--;
		}
		else {
			item--;
		}
	}
}