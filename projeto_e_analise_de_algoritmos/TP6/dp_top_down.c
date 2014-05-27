#include <stdio.h>
#define max(a,b) (a > b ? a : b)

int matrix[100][100] = {0};
int picks[100][100] = {0};

int knapsack(int index, int size, int weights[],int values[]){
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
        take = values[index] + knapsack(index-1, size-weights[index], weights, values);

    dontTake = knapsack(index-1, size, weights, values);

    matrix[index][size] = max (take, dontTake);

    if (take>dontTake)
        picks[index][size]=1;
    else
        picks[index][size]=-1;

    return matrix[index][size];

}

void printPicks(int item, int size, int weights[]){

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

    printf("n");

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

    // First line of data is item count, knapsack capacity
    int n, W;
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &W);

    // Make arrays of weights and values
    int vals[n], wts[n], i = 0, j = 0, index = 0;
    while (!feof (fp) && index < n)
        {
          fscanf(fp, "%d", &j);
          wts[index++] = j;
          //index++;
        }
        //int k=0;
        printf("passei\n");
        index = 0;
        while (!feof (fp) && index < n)
        {
          fscanf(fp, "%d", &i);
          vals[index++] = i;
          //index++;
        }
    fclose(fp);

    printf("Max value = %dnn",knapsack(n-1, W, wts, vals));

    printf("Picks were: ");
    printPicks(n-1, W, wts);
    
  }
    return 0;
}