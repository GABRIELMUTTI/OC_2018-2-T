#include <stdlib.h>
#include "instance.h"

#define OUT_SUCCESS 0
#define ERR_MALLOC -1

// Defines a solution to a instance;
typedef struct solution_s
{
    unsigned int** coloration;
    
} Solution;

int newSolution(Solution* solution, Instance* instance);

int checkFactibility(Instance* instance, Solution* solution);
void colorVertex(Solution* solution, unsigned int vertex, unsigned int color);


