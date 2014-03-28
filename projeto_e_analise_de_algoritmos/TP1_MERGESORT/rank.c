#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct
{
    int id;
    int major;
    int misc;
} Evaluation;

Evaluation *generate_random_evaluations( int n );

void bubblesort_evaluations( Evaluation *evals, int n );

void merge_sort_com_recursao( Evaluation *evals, int n );

void merge_sort_sem_recursao( Evaluation *evals, int n );

void merge_sort_ordena( Evaluation *evals, int esq, int dir );

void merge_sort_intercala( Evaluation *evals, int esq, int meio, int dir ); 

void check_sorting( Evaluation *evals, int n );

void print_evals( Evaluation *evals, int n );

int main( int argc, const char **argv )
{
    if (argc<2)
    {
        fprintf( stderr, "usage: \n\trank n" );
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    printf("generating %d random evaluations.\n", n); fflush(stdout);
    Evaluation *evals = generate_random_evaluations( n );

    clock_t start = clock();
    printf("sorting ... " ); fflush(stdout);

    merge_sort_sem_recursao(evals, n);

    clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("done in %.3f.\n", cpuTime ); fflush(stdout);

    printf("checking result.\n" ); fflush(stdout);
    check_sorting( evals, n );

    if (n<200)
        print_evals( evals, n );

    free( evals );

    return EXIT_SUCCESS;
}

Evaluation *generate_random_evaluations( int n )
{
    Evaluation *eval = malloc( sizeof(Evaluation)*n );
    assert( eval != NULL );

    int i;
    for ( i=0 ; (i<n) ; ++i )
    {
        eval[i].id = i+1;
        eval[i].major = rand()%100;
        eval[i].misc = rand()%100;
    }
    return eval;
};

void bubblesort_evaluations( Evaluation *evals, int n )
{
    char swapped;
    do
    {
        swapped = 0;
        int i;
        for ( i=0 ; (i<n-1) ; i++ )
        {
            if ( (evals[i].major < evals[i+1].major) ||
                 ((evals[i].major == evals[i+1].major) && (evals[i].misc < evals[i+1].misc)) )
            {
                Evaluation aux = evals[i];
                evals[i] = evals[i+1];
                evals[i+1] = aux;
                swapped = 1;
            }
        }
    } while (swapped);
}

void check_sorting( Evaluation *evals, int n )
{
    int i;
    for ( i=0 ; (i<n-1) ; ++i )
    {
        if ( (evals[i].major < evals[i+1].major) ||
             ((evals[i].major == evals[i+1].major) && (evals[i].misc < evals[i+1].misc)) )
        {
            printf("%d, %d\n", evals[i].major, evals[i+1].major);
            fprintf( stderr, "error: elements %d and %d are not properly ordered!\n", i, i+1 );
            exit( EXIT_FAILURE );
        }
    }
}

void print_evals( Evaluation *evals, int n )
{
    int i;
    for ( i=0 ; (i<n) ; ++i )
        printf("id: %02d major score: %03d minor score: %03d\n", evals[i].id, evals[i].major, evals[i].misc );
}

void merge_sort_com_recursao(Evaluation *evals, int n) {
    merge_sort_ordena(evals, 0, n-1);
}

void merge_sort_ordena( Evaluation *evals, int esq, int dir ) {     
    if (esq == dir)
        return;
    int meio = (esq + dir) / 2;
    merge_sort_ordena(evals, esq, meio);
    merge_sort_ordena(evals, meio+1, dir);
    merge_sort_intercala(evals, esq, meio, dir);
    return;
}

void merge_sort_intercala( Evaluation *evals, int esq, int meio, int dir ) { 
    int i, j, k;
    int a_tam = meio-esq+1;
    int b_tam = dir-meio;
    Evaluation *a = (Evaluation*) malloc(sizeof(Evaluation) * a_tam);
    Evaluation *b = (Evaluation*) malloc(sizeof(Evaluation) * b_tam);

    for (i = 0; i < a_tam; i++)
        a[i] = evals[i+esq];
    for (i = 0; i < b_tam; i++)
        b[i] = evals[i+meio+1];

    for (i = 0, j = 0, k = esq; k <= dir; k++) {
        if (i == a_tam)
            evals[k] = b[j++];
        else if (j == b_tam)
            evals[k] = a[i++];
        else if ((a[i].major < b[j].major) || ((a[i].major == b[j].major) && (a[i].misc < b[j].misc)))
            evals[k] = b[j++];
        else
            evals[k] = a[i++];
    }
    free(a);
    free(b);
}

void merge_sort_sem_recursao( Evaluation *evals, int n ) {
    int esq, dir;
    int salto = 1;
    while (salto < n) {
        esq = 0;
        while (esq + salto < n) {
            dir = esq + 2*salto;
            if (dir > n)
                dir = n;
            merge_sort_intercala(evals, esq, esq+salto-1, dir-1);
            esq = esq + 2*salto;
        }
        salto = 2*salto;
    }
}
