#include "cmb.h"

Instance* newInstance(unsigned int k, unsigned int numVertices, unsigned int* graph, unsigned int* weights)
{
    Instance* instance = malloc(sizeof(Instance));
    if (instance == 0) { return instance; }

    instance->k = k;
    instance->numVertices = numVertices;
    instance->graph = graph;
    instance->weights = weights;

    return instance;
}

void destroyInstance(Instance* instance)
{
    free(instance->graph);
    free(instance->weights);
    free(instance);
}

int checkFactibility(Instance* instance, Solution* solution)
{
    // O(n^2)
    unsigned int i;
    unsigned int j;
    for (i = 0; i < instance->numVertices; i++)
    {
	unsigned int vertexColor = solution->coloration[i];
	
	for (j = 0; j < instance->numVertices; j++)
	{
	    if (solution->coloration[j] == vertexColor && existsEdge(instance, i, j))
	    {
		return false;
	    }
	}
	
    }
    return true;
}
