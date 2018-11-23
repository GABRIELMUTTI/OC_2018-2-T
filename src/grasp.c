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

	if (solutionValue < bestSolutionValue)
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

int bestImprovementLocalSearch(Instance* instance, Solution** solution, float* solutionValue)
{
    unsigned int numNeighbours;
    float bestValue, neighbourValue;
    Solution** neighbours;
    Solution* bestSolution;
    
    int haveImproved = 1;
    unsigned int i;
    do
    {
	if (findNeighbours(instance, bestSolution, &neighbours, &numNeighbours) != 0) { return -1; }

	for (i = 0; i < numNeighbours; i++)
	{
	    neighbourValue = getValue(instance, neighbours[i]);
	    if (neighbourValue < bestValue)
	    {
		// The better way to do this is to manipulate the solution instead of copy it.
		// For now we’ll do this.
		bestSolution = neighbours[i];
		bestValue = neighbourValue;
	    }
	}
		
    } while(haveImproved);

    *solutionValue = bestValue;
    *solution = bestSolution;
    
    return 0;
}

int findNeighbours(Instance* instance, Solution* solution, Solution*** neighbours, unsigned int* numNeighbours)
{

    return 0;
}
