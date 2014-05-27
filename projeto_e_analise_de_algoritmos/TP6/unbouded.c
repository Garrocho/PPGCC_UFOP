/*
 * a knapsack 0/1 algorithm
 */

/*
 * Copyright (c) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

int** knapsack01(int *w, int *v, size_t n, int W, int *V);

int** knapsack01(int *w, int *v, size_t n, int W, int *V) {
	int i,j;
	int **c = (int**) NULL;

	c = (int**) malloc(sizeof(int*)*(n+1));
	*c = (int*)malloc(sizeof(int)*(W+1));

	for ( i = 0; i <= W; i++ ) {
		c[0][i] = 0;
	}

	for ( i = 1; i <= n; i++ ) {
		*(c+i) = (int*)malloc(sizeof(int)*(W+1));

		c[i][0] = 0;

		for ( j = 1; j <= W; j++ ) {

			if ( *(w+i-1) <= j ) {
				if ( *(v+i-1) + c[i-1][j-*(w+i-1)] > c[i-1][j] ) {
					c[i][j] = *(v+i-1)+c[i-1][j-*(w+i-1)];
				} else {
					c[i][j] = c[i-1][j];
				}
			} else {
				c[i][j] = c[i-1][j];
			}
		}
	}

	*V = c[n][W];

	return c;
}
int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Uso: ./a.out <arquivo>\n");
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

		// First line of data is item count, knapsack capacity
		int n, W;
		fscanf(fp, "%d", &n);
		fscanf(fp, "%d", &W);

		// Make arrays of weights and values
		int vals[n], wts[n], i = 0, j = 0, index = 0;
		while (!feof (fp) && index < n)
		{
			if (fscanf(fp, "%d", &i) != 1) {
		        return EXIT_FAILURE; // Handle the error appropriately.
		    }
		    if (fscanf(fp, "%d", &j) != 1) {
		        return EXIT_FAILURE; // Handle the error appropriately.
		    }
			//fscanf(fp, "%d", &i);
			//fscanf(fp, "%d", &j);
			vals[index] = i;
			wts[index] = j;
			index++;
		}
		fclose(fp);

        int V;

		//w = (int*) malloc(sizeof(int)*n);
		//v = (int*) malloc(sizeof(int)*n);

		knapsack01(wts, vals, n, W, &V);

		printf("%d\n", V);

		//free(w);
		//free(v);

		//for ( i = 0; i <= n; i++ ) {
		//	free(*(c+i));
		//}
		
		//free(c);

		exit(0);

	}
	return 0;
}