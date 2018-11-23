#include "../include/solution.h"

int newSolution(Solution** solution, Instance* instance)
{
    *solution = malloc(sizeof(Solution));
    if (*solution == NULL) { return ERR_MALLOC; }

    (*solution)->coloration = malloc(sizeof(unsigned int*) * instance->numColors);
    if ((*solution)->coloration == 0) { return ERR_MALLOC; }
    
    return OUT_SUCCESS;
}

void destroySolution(Solution* solution)
{
    free(solution->coloration);
    free(solution);
}

int checkFactibility(Instance* instance, Solution* solution)
{
    unsigned int i;
    unsigned int j;
    for (i = 0; i < instance->numVertices; i++)
    {
	for (j = 0; j < instance->numVertices; j++)
	{
	    int areSameColors = solution->coloration[i] == solution->coloration[j];
	    int edge = existsEdge(instance, i, j);
	    
	    if (areSameColors && i != j && edge)
	    {
		return 0;
	    }
	}
    }

    return 1;
}
   
void colorVertex(Solution* solution, unsigned int vertex, unsigned int color)
{
    solution->coloration[vertex] = color;
}

SolutionValue getValue(Instance* instance, Solution* solution)
{
    SolutionValue solutionValue;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);

    unsigned int i;
    for (i = 0; i < instance->numColors; i++)
    {
	solutionValue.colorValues[i] = 0.0f;
    }

    for(i = 0; i < instance->numVertices; i++)
    {
	unsigned int color = solution->coloration[i];
	solutionValue.colorValues[color] += instance->weights[i];
    }


    float heaviestColorValue = solutionValue.colorValues[0];
    for (i = 1; i < instance->numColors; i++)
    {
	if (solutionValue.colorValues[i] < heaviestColorValue)
	{
	    heaviestColorValue = solutionValue.colorValues[i];
	}
    }

    return solutionValue;
}
