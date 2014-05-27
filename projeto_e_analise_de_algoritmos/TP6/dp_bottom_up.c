#include <stdio.h>

#define max(a,b) (a > b ? a : b)

int matrix[400][400] = {0};
int picks[400][400] = {0};

int knapsack(int nItems, int size, int weights[], int values[]){
    int i,j;

    for (i=1;i<=nItems;i++){
        for (j=0;j<=size;j++){
            if (weights[i-1]<=j){
                matrix[i][j] = max(matrix[i-1][j],values[i-1]+matrix[i-1][j-weights[i-1]]);
                if (values[i-1]+matrix[i-1][j-weights[i-1]]>matrix[i-1][j])
                    picks[i][j]=1;
                else
                    picks[i][j]=-1;
            }
            else{
                picks[i][j] = -1;
                matrix[i][j] = matrix[i-1][j];
            }
        }
    }

    return matrix[nItems][size];

}

void printPicks(int item, int size, int weights[]){

    while (item>0){
        if (picks[item][size]==1){
            printf("%d ",item-1);
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
    while (!feof (fp) && index < n/2)
    {
      fscanf(fp, "%d", &j);
      wts[index] = j;
      index++;
    }
    int k=0;
    printf("passei\n");
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
    printf("passei\n");
    fclose(fp);

    printf("Max value = %d",knapsack(n-1, W, wts, vals));

    printf("Picks were: ");
    printPicks(n-1, W, wts);
    
  }
    return 0;
}