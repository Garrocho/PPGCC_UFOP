#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int max(int x, int y);
 
void knapsack(int n, int W, int wts[], int vals[], int K[n+1][W+1]);

int kmax(int n, int W, int K[n+1][W+1]);

void traceback(int n, int W, int K[n+1][W+1], char taken[], int wts[]);

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

    // First line of data is item count, knapsack capacity
    int n, W;
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &W);

    // Make arrays of weights and values
    int vals[n], wts[n], i = 0, j = 0, index = 0;
    while (!feof (fp) && index < n)
    {
      fscanf(fp, "%d", &i);
      fscanf(fp, "%d", &j);
      vals[index] = i;
      wts[index] = j;
      index++;
    }
    fclose(fp);

    int K[n+1][W+1];
    knapsack(n, W, wts, vals, K);

    char taken[n];
    memset(taken,'0',sizeof(taken));
    traceback(n, W, K, taken, wts);

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