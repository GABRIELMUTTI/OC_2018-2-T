#include "../include/grasp.h"

int grasp(Instance* instance, Solution** solution, float* value, unsigned int numIterations)
{
    if (*solution == NULL)
    {
	*solution = malloc(sizeof(Solution));
	if (*solution == NULL) { return -3; }
    }
    
    Solution* currentSolution, *bestSolution;
    float bestSolutionValue, solutionValue;
    
    unsigned int iterationCounter = 0;
    do
    {
	if (greedySolutionFinder(instance, &currentSolution) != 0) { return -1; }
	if (bestImprovementLocalSearch(instance, &currentSolution, &solutionValue)) { return -2; }

	if (solutionValue > bestSolutionValue)
	{
	    bestSolution = currentSolution;
	    bestSolutionValue = solutionValue;
	}

	iterationCounter++;
    } while(iterationCounter < numIterations);

    *value = bestSolutionValue;
    *solution = bestSolution;
    
    return 0;
}

int greedySolutionFinder(Instance* instance, Solution** solution)
{

    return 0;
}

int bestImprovementLocalSearch(Instance* instance, Solution** currentSolution, float* solutionValue)
{

    return 0;
}
