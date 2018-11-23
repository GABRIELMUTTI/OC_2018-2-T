#ifndef __GRASP_H__
#define __GRASP_H__

#include "../include/instance.h"
#include "../include/solution.h"

#include <stddef.h>
#include <math.h>

typedef struct neighbour_s
{
    unsigned int inColor;
    unsigned int outColor;
    unsigned int vertex;
    
} Neighbour;



int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations);
int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue);
int bestImprovementLocalSearch(Instance* instance, Solution** currentSolution, SolutionValue* solutionValue);
int findNeighbours(Instance* instance, Solution* solution, Neighbour** neighbours, unsigned int* numNeighbours);


#endif // __GRASP_H__
