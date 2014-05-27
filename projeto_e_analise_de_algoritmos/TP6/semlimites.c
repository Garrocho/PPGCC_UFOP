#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
int max_weight;
 
typedef struct { int w, v, qty; } item_t;
 
item_t* items;
int n_items;

typedef struct {
	int v, w;		   /* value & weight total */
	unsigned short n[50]; /* num of each item taken */
} solution_t, *solution;
 
solution_t *cache, *blank;
 
int init_cache()
{
	/* a flat array.  If problem size is large, might be a bad idea;
	 * then again, other caching method face similar issue, too
	 */
	size_t i;
	size_t n_rec = (max_weight + 1) * n_items;
	cache = calloc(sizeof(solution_t), (n_rec + 1));
	if (!cache) return 0;
 
	for (i = 0; i <= n_rec; i++) {
		cache[i].v = -1;  /* value = -1 means cache not used yet */
		cache[i].w = 0;
	}
	(blank = cache + n_rec)->v = 0;
	return 1;
}
 
solution solve(int weight, int pos)
{
	int i, w, v, qty;
	solution sol, best = 0, ret;
 
	if (pos < 0) return blank;
 
	ret = &cache[weight * n_items + pos];
	if (ret->v >= 0) return ret;
 
	w   = items[pos].w;
	v   = items[pos].v;
	qty = items[pos].qty;
 
	for (i = 0; i <= qty && weight >= 0; i++, weight -= w) {
		sol = solve(weight, pos - 1);
		if (sol->v + i * v <= ret->v) continue;
 
		best = sol;
		ret->v = best->v + v * i;
		ret->n[pos] = i;
	}
 
	/*  only happens if there are no solution at all, i.e.
	 *  max_weight too small to hold even one item
	 */
	if (ret->v <= 0) return blank;
 
	ret->w = best->w + w * ret->n[pos];
	memcpy(ret->n, best->n, sizeof(unsigned short) * pos);
 
	return ret;
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

		int n, W;
		fscanf(fp, "%d", &n_items);
		fscanf(fp, "%d", &W);
		max_weight = W;

		items = (item_t*)malloc(sizeof(item_t)*n_items);
		int i = 0, j = 0, index = 0;
		
		while (!feof (fp) && index < n_items)
		{
			fscanf(fp, "%d", &i);
			fscanf(fp, "%d", &j);
			items[index].v = j;
			items[index].w = i;
			items[index].qty = 1;
			index++;
		}
		fclose(fp);

		solution x;
 
	init_cache();
	x = solve(max_weight, n_items);
 
	/*printf("Taking:\n");
	for (i = 0; i < n_types; i++) {
		if (! x->n[i]) continue;
		printf("  %hu %s\n", x->n[i], items[i].name);
	}*/
 
	printf("Weight: %d Value: %d\n", x->w, x->v);

		/*i = 0;
		int w = 0;
		solucao s = {0, 0};
		mochila(W, n_items - 1, &s);

		for (i = 0; i < n_items; i++) {
			if (s.bits & (1 << i)) {
				w += item[i].peso;
			}
		}
		printf("Lucro Maximo: %d; Peso: %d\n", s.valor, w);*/
	}
	return 0;
}
/*
int main()
{
	int i;
	solution x;
 
	init_cache();
	x = solve(max_weight, n_types - 1);
 
	/*printf("Taking:\n");
	for (i = 0; i < n_types; i++) {
		if (! x->n[i]) continue;
		printf("  %hu %s\n", x->n[i], items[i].name);
	}
 
	printf("Weight: %d Value: %d\n", x->w, x->v);
 
	/* free(cache); 
	return 0;
}*/