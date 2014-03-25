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
