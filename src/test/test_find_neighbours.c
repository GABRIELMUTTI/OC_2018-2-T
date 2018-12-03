#include "../../include/test/test_find_neighbours.h"


int testFindNeighbours(const char* filepath)
{
    Instance* instance = NULL;

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
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
    greedySolutionFinder(instance, &solution, &solutionValue, alpha);


    for (i = 0; i < instance->numVertices; i++)
    {
	printf("v%d color: %d\n", i, solution->coloration[i]);
    }
    
    unsigned int numNeighbours;
    Neighbour* neighbours = NULL;
    if (findNeighbours(instance, solution, &neighbours, &numNeighbours) != 0)
    {
	return TST_ERR_FIND_NEIGHBOURS;
    }

    printf("numNeighbours: %d\n", numNeighbours);

    for (i = 0; i < numNeighbours; i++)
    {
	printf("v %d: %d -> %d\n", neighbours[i].vertex, neighbours[i].outColor, neighbours[i].inColor);
    }
    
    return 0;
}
