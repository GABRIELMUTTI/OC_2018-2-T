#ifndef __GRASP_H__
#define __GRASP_H__

#include "../include/instance.h"
#include "../include/solution.h"

#include <stddef.h>

int grasp(Instance* instance, Solution** solution, float* value, unsigned int numIterations);
int greedySolutionFinder(Instance* instance, Solution** solution);
int bestImprovementLocalSearch(Instance* instance, Solution** currentSolution, float* solutionValue);
int findNeighbours(Instance* instance, Solution* solution, Solution*** neighbours, unsigned int* numNeighbours);


#endif // __GRASP_H__
