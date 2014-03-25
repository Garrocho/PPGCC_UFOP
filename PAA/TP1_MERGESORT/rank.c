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
