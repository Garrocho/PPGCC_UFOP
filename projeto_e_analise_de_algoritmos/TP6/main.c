#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Uso: ./a.out <arquivos>\n");
		return 1;
	}

	else
	{
		char* infile = argv[1];
		FILE* fp = fopen(infile, "r");
		if (fp == NULL)
		{
			printf("Nao pode abrir %s.\n", infile);
			return 2;
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
		fclose(fp);
		printf("Top Down\n");
		printf("Lucro Otimo = %d\n", top_down(n-1, W, wts, vals, matrix, picks));
		printf("Selecionados = ");
		print_picks(n-1, W, wts, picks);

		for (i=0; i < n; i++) {
			for (j=0; j <= W; j++) {
				matrix[i][j] = 0;
				picks[i][j] = 0;
			}
		}
		
		printf("\nBottom Up\n");
		printf("Lucro Otimo = %d\n", bottom_up(n-1, W, wts, vals, matrix, picks));
		printf("Selecionados = ");
		print_picks(n-1, W, wts, picks);

	}
	return 0;
}