#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (a > b ? a : b)

int knapsack(int index, int size, int *weights, int *values, int **matrix, int **picks){
    int take,dontTake;

    take = dontTake = 0;

    if (matrix[index][size]!=0)
        return matrix[index][size];

    if (index==0){
        if (weights[0]<=size){
            picks[index][size]=1;
            matrix[index][size] = values[0];
            return values[0];
        }
        else{
            picks[index][size]=-1;
            matrix[index][size] = 0;
            return 0;
        }
    }

    if (weights[index]<=size)
        take = values[index] + knapsack(index-1, size-weights[index], weights, values, matrix, picks);

    dontTake = knapsack(index-1, size, weights, values, matrix, picks);

    matrix[index][size] = max (take, dontTake);

    if (take>dontTake)
        picks[index][size]=1;
    else
        picks[index][size]=-1;

    return matrix[index][size];

}

void printPicks(int item, int size, int *weights, int **picks){

    while (item>=0){
        if (picks[item][size]==1){
            printf("%d ",item);
            item--;
            size -= weights[item];
        }
        else{
            item--;
        }
    }

    printf("\n");
    return;
}

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
        matrix[i] = (int*)calloc(n, sizeof(int));
        picks[i] = (int*)calloc(n, sizeof(int));
        printf("%d %d\n", matrix[i][0], picks[i][0]);
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

    printf("Lucro Otimo = %d\n", knapsack(n-1, W, wts, vals, matrix, picks));
    printf("Selecionados = ");
    printPicks(n-1, W, wts, picks);
    
  }
    return 0;
}