#ifndef __PATH_RELINKING_H__
#define __PATH_RELINKING_H__

#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/greedy.h"
#include "../include/local_search.h"

#include <time.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

typedef struct delta_s
{
    uint vertex;
    uint color;
} Delta;

int pathRelinking(Instance* instance, Solution** eliteSolutions, SolutionValue* eliteValues, uint numElites, Solution* solution, SolutionValue* solutionValue, uint* out_numConflicts);
int getDelta(Instance* instance, Solution* s1, Solution* s2, Delta** out_deltas, uint* out_numDeltas);


#endif // __PATH_RELINKING_H__
