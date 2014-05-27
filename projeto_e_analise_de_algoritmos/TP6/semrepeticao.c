#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
 
typedef struct {
	int peso, valor;
} item_t;
 
item_t* item;
 
typedef struct {
	uint32_t bits;
	int valor;
} solucao;

int n_items;
 
void mochila(int peso, int idx, solucao *s)
{
	solucao v1, v2;
	if (idx < 0) {
		s->bits = s->valor = 0;
		return;
	}

	if (peso < item[idx].peso) {
		mochila(peso, idx - 1, s);
		return;
	}

	mochila(peso, idx - 1, &v1);
	mochila(peso - item[idx].peso, idx - 1, &v2);

	v2.valor += item[idx].valor;
	v2.bits |= (1 << idx);

	*s = (v1.valor >= v2.valor) ? v1 : v2;
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

		item = (item_t*)malloc(sizeof(item_t)*n_items);
		int i = 0, j = 0, index = 0;
		
		while (!feof (fp) && index < n_items)
		{
			fscanf(fp, "%d", &i);
			fscanf(fp, "%d", &j);
			item[index].valor = j;
			item[index].peso = i;
			index++;
		}
		fclose(fp);

		i = 0;
		int w = 0;
		solucao s = {0, 0};
		mochila(W, n_items - 1, &s);

		for (i = 0; i < n_items; i++) {
			if (s.bits & (1 << i)) {
				w += item[i].peso;
			}
		}
		printf("Lucro Maximo: %d; Peso: %d\n", s.valor, w);
	}
	return 0;
}