#include "../include/instance.h"

int newInstance(Instance* instance, unsigned int numColors, unsigned int numVertices)
{
    instance->numColors = numColors;
    instance->numVertices = numVertices;

    instance->weights = malloc(sizeof(float) * numVertices);
    if (instance->weights == 0) { return ERR_MALLOC; }

    instance->graph = malloc(sizeof(unsigned int*) * numVertices);
    if (instance->graph == 0) { return ERR_MALLOC; }
    
    unsigned int i;
    unsigned int j;
    for (i = 0; i < numVertices; i++)
    {
	instance->graph[i] = malloc(sizeof(unsigned int) * numVertices);
	if (instance->graph[i] == 0) { return ERR_MALLOC; }
	    
	for (j = 0; j < numVertices; j++)
	{
	    instance->graph[i][j] = 0;
	}
    }
    
    return OUT_SUCCESS;
}

void addEdge(Instance* instance, unsigned int v, unsigned int u)
{
    instance->graph[v][u] = 1;    
}

void setWeight(Instance* instance, unsigned int vertex, float weight)
{
    instance->weights[vertex] = weight;
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
