#ifndef MOCHILA_H
#define MOCHILA_H

#define max(a, b) (a > b ? a : b)

int top_down(int, int, int*, int*, int**, int**);

int bottom_up(int, int, int*, int*, int**, int**);

void print_picks(int, int, int*, int**);

#endif /* MOCHILA_H */