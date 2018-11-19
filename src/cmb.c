#include "cmb.h"

Instance* newInstance(unsigned int numColors, unsigned int numVertices, unsigned int** graph, unsigned int* weights)
{
    Instance* instance = malloc(sizeof(Instance));
    if (instance == 0) { return instance; }

    instance->numColors = numColors;
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

int existsEdge(Instance* instance, unsigned int v, unsigned int u)
{
    return instance->graph[v][u];
}

int checkFactibility(Instance* instance, Solution* solution)
{
    unsigned int colorIndex;
    for (colorIndex = 0; colorIndex < instance->numColors; colorIndex++)
    {
	unsigned int* currentColorArray = solution->coloration[colorIndex];
	unsigned int sizeColorArray = solution->sizeColors[colorIndex];

	unsigned int i;
	unsigned int j; 
	for (i = 0; i < sizeColorArray; i++)
	{
	    for (j = 0; j < sizeColorArray; j++)
	    {
		if (existsEdge(instance, currentColorArray[i], currentColorArray[j]))
		{
		    return 0;
		}
	    }   
	}
    }
    
    return 1;
}















