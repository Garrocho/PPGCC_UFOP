#ifndef MOCHILA_H
#define MOCHILA_H

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

int top_down(int, int, int*, int*, int**, int**);

int bottom_up(int, int, int*, int*, int**, int**);

int count_picks(int, int, int *, int **);

void print_picks(int, int, int*, int**, FILE*);

#endif /* MOCHILA_H */