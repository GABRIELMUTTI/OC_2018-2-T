#include "../../include/test/test_find_neighbours.h"


int testFindNeighbours(const char* filepath)
{
    const float EPSILON = 1e-12;
    Instance* instance = NULL;

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }

    VertexWeight* sortedWeights = NULL;
    if (sortWeights(instance, &sortedWeights) != 0)
    {
	return TST_ERR_SORT_WEIGHTS;
    }


    SolutionValue solutionValue;
    solutionValue.bestValue = 0.0f;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);
    
    unsigned int i;
    for (i = 0; i < instance->numColors; i++)
    {
	solutionValue.colorValues[i] = 0.0f;
    }
    float alpha = 0.02f;
    
    Solution* solution = NULL;
    if (greedySolutionFinder(instance, &solution, &solutionValue, sortedWeights, alpha) != 0)
    {
	return TST_ERR_GREEDY_SOLUTION_FINDER;
    }

    unsigned int numNeighbours;
    Neighbour* neighbours = NULL;
    if (findNeighbours(instance, solution, &neighbours, &numNeighbours) != 0)
    {
	return TST_ERR_FIND_NEIGHBOURS;
    }
    
    
    return 0;
}
