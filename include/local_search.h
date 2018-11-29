#ifndef __LOCAL_SEARCH_H__
#define __LOCAL_SEARCH_H__

#include "../include/instance.h"
#include "../include/solution.h"

#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct neighbour_s
{
    unsigned int inColor;
    unsigned int outColor;
    unsigned int vertex;
    
} Neighbour;


int bestImprovementLocalSearch(Instance* instance, Solution* currentSolution, SolutionValue* solutionValue, unsigned int numConflicts, unsigned int maxDegree);
int findNeighbours(Instance* instance, Solution* solution, Neighbour** neighbours, unsigned int* numNeighbours);
int checkNeighbourFactible(Instance* instance, Solution* solution, Neighbour neighbour, unsigned int numConflicts);


#endif // __LOCAL_SEARCH_H__
