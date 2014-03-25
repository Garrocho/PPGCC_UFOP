#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct
{
    int id; /* unique identifier of the candidate */
    /* there are two different scores,  sorting should be done in lexicographic order (major, minor) */
    int major; /* score in major subjects */
    int misc; /* score in miscellaneous subjects, used only to break ties */
} Evaluation;

/* generates randonly a vector with n evaluations */
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


    clock_t start = clock(); /* measuring CPU time with clock() :
                                precise but gives overflow if processing time is very large (many hours) */

    printf("sorting ... " ); fflush(stdout);

    merge_sort_sem_recursao(evals, n);

    clock_t end = clock();
    double cpuTime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("done in %.3f.\n", cpuTime ); fflush(stdout);


    printf("checking result.\n" ); fflush(stdout);
    check_sorting( evals, n );

    /* printing only if the output is not too large */
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
