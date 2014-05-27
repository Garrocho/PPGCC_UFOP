#include <stdio.h>
#include <stdlib.h>
#include "mochila.h"

int top_down(int index, int size, int *weights, int *values, int **matrix, int **picks) {
	int take, dontTake;

	take = dontTake = 0;

	if (matrix[index][size] != 0)
		return matrix[index][size];

	if (index == 0) {
		if (weights[0] <= size ) {
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

	if (weights[index] <= size)
		take = values[index] + top_down(index-1, size-weights[index], weights, values, matrix, picks);

	dontTake = top_down(index-1, size, weights, values, matrix, picks);
	matrix[index][size] = max(take, dontTake);

	if (take > dontTake)
		picks[index][size]=1;
	else
		picks[index][size]=-1;

	return matrix[index][size];
}

int bottom_up(int nItems, int size, int *weights, int *values, int **matrix, int **picks) {
	int i,j;

	for (i=1; i <= nItems; i++){
		for (j=0; j <= size; j++){
			if (weights[i-1] <= j){
				matrix[i][j] = max(matrix[i-1][j], values[i-1] + matrix[i-1][j-weights[i-1]]);
				if (values[i-1] + matrix[i-1][j-weights[i-1]] > matrix[i-1][j])
					picks[i][j] = 1;
				else
					picks[i][j] = -1;
			}
			else{
				picks[i][j] = -1;
				matrix[i][j] = matrix[i-1][j];
			}
		}
	}
	return matrix[nItems][size];
}

void print_picks(int item, int size, int *weights, int **picks, FILE *arquivo) {

	while (item >= 0) {
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