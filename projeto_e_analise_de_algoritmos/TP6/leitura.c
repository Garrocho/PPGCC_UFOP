// A Dynamic Programming based solution for 0-1 Knapsack problem
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// compute max of ints
int max(int x, int y);
 
// Basic bottom up approach to fill a knapsack of capacity W from n items with 
//  weights (wts[]) and values (vals[])
void knapsack(int n, int W, int wts[], int vals[], int K[n+1][W+1]);

// Return knapsack value
int kmax(int n, int W, int K[n+1][W+1]);

// traceback to determine which items were taken
void traceback(int n, int W, int K[n+1][W+1], char taken[], int wts[]);

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./knapsack infile\n");
        return 1;
	}
	
	else
	{
		// open input file 
		char* infile = argv[1];
		FILE* fp = fopen(infile, "r");
		if (fp == NULL)
		{
			printf("Could not open %s.\n", infile);
			return 2;
		}

		// First line of data is item count, knapsack capacity
		int n, W;
		fscanf(fp, "%d %d", &n, &W);

		// Make arrays of weights and values
		int vals[n], wts[n], i = 0, j = 0, index = 0;
		while (!feof (fp) && index < n)
		{
			fscanf(fp, "%d %d", &i, &j);
			vals[index] = i; wts[index] = j;
			index++;
		}
		fclose(fp);

		// Fill 2-d array
		int K[n+1][W+1];
		knapsack(n, W, wts, vals, K);

		// Traceback to find items taken
		char taken[n];
		memset(taken,'0',sizeof(taken));
		traceback(n, W, K, taken, wts);
	
		/* printf("Item count: %d\nCapacity: %d\n", n, W); */
		/* for (int i = 0; i < n; i++) */
		/* { */
		/* 	printf("Item %d: value = %d, weight = %d\n", i, vals[i], wts[i]); */
		/* } */
	
		// Output max value and taken items as string of 0,1s
		// write answer to standard output:
		printf("%d %d\n ", kmax(n, W, K), 0);
		printf("%c",taken[0]);
		for(i = 1; i < n; i++) 
		{
			printf(" %c", taken[i]);
			if (i == n - 1)
				printf("\n");
		}
		printf("%c", '\n');
	}
    return 0;
}

int max(int x, int y) { 
	return (x > y) ? x : y; 
}

void knapsack(int n, int W, int wts[], int vals[], int K[n+1][W+1])
{
   int i, w; 
   // fill 2-d array
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wts[i-1] <= w)
                 K[i][w] = max(vals[i-1] + K[i-1][w-wts[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
}

int kmax(int n, int W, int K[n+1][W+1])
{
	return K[n][W];
}

void traceback(int n, int W, int K[n+1][W+1], char taken[], int wts[])
{
	int i = n, j = W;
	while (i > 0)
	{
		if (K[i][j] != K[i-1][j])
		{
			taken[i-1] = '1';
			j -= wts[i-1];
		}
		i--;
	}
}
