#include "../include/solution.h"

int newSolution(Solution** solution, Instance* instance)
{
    *solution = malloc(sizeof(Solution));
    if (*solution == NULL) { return ERR_MALLOC; }

    (*solution)->coloration = malloc(sizeof(unsigned int) * instance->numVertices);
    if ((*solution)->coloration == NULL) { return ERR_MALLOC; }

    (*solution)->numVertexPerColor = malloc(sizeof(unsigned int) * instance->numColors);
    if ((*solution)->numVertexPerColor == NULL) { return ERR_MALLOC; }
    
    return OUT_SUCCESS;
}

int newSolutionValue(SolutionValue* value, Instance* instance)
{

    value->colorValues = malloc(sizeof(float) * instance->numColors);


    return 0;
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
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (instance->graph[i][j] == 1 && solution->coloration[i] == solution->coloration[j])
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

int checkVertexFactibility(Instance* instance, Solution* solution, unsigned int vertex)
{
    unsigned int i;
    unsigned int vertexColor = solution->coloration[vertex];

    for (i = 0; i < instance->numVertices; i++)
    {
	if (i != vertex && instance->graph[vertex][i] == 1 && solution->coloration[i] == vertexColor)
	{
	    return 0;
	}
    }
    
    return 1;
}

int countConflicts(Instance* instance, Solution* solution, unsigned int vertex)
{
    int conflicts = 0;
    
    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	if (i != vertex && solution->coloration[i] == solution->coloration[vertex] && instance->graph[vertex][i] == 1)
	{
	    conflicts++;
	}
	
    }

    return conflicts;
}

unsigned int countSolutionConflicts(Instance* instance, Solution* solution)
{
    unsigned int conflicts = 0;

    unsigned int i, j;

    for (i = 0; i < instance->numVertices; i++)
    {
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (solution->coloration[i] == solution->coloration[j] && instance->graph[i][j] == 1)
	    {
		conflicts++;
	    }
	}
    }


    return conflicts;
}

void getVertexNeighbours(Instance* instance, Solution* solution, uint vertex, uint** out_neighbours, uint** out_neighboursColor, uint* out_numNeighbours)
{
    *out_neighbours = malloc(sizeof(uint) * instance->numVertices);
    *out_neighboursColor = malloc(sizeof(uint) * instance->numVertices);
    *out_numNeighbours = 0;
    
    uint i;
    for (i = 0; i < instance->numVertices; i++)
    {
	if (instance->graph[vertex][i] == 1 && vertex != i)
	{
	    (*out_neighbours)[*out_numNeighbours] = i;
	    (*out_neighboursColor)[*out_numNeighbours] = solution->coloration[i];
	    (*out_numNeighbours)++;
	}
    }
}

void getVertexNeighboursInfo(Instance* instance, Solution* solution, uint vertex, uint* out_neighbours, uint* out_neighboursColor, uint* out_colorCounts, uint* out_numConflicts, uint* out_numNeighbours)
{
    *out_numNeighbours = 0;
    *out_numConflicts = 0;

    uint i;
    for (i = 0; i < instance->numColors; i++)
    {
	out_colorCounts[i] = 0;
    }

    uint vertexColor = solution->coloration[vertex];
    
  
    for (i = 0; i < instance->numVertices; i++)
    {
	if (instance->graph[vertex][i] == 1 && vertex != i)
	{
	    uint neighbourColor = solution->coloration[i];
	    
	    out_neighbours[*out_numNeighbours] = i;
	    out_neighboursColor[*out_numNeighbours] = neighbourColor;
	    out_colorCounts[neighbourColor]++;
	    (*out_numNeighbours)++;

	    if (vertexColor == neighbourColor)
	    {
		(*out_numConflicts)++;
	    }
	}
    }
}


void printSolution(Instance* instance, Solution* solution)
{
    printf("Solution:\n");
    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	printf("\tv %d -> c %d\n", i, solution->coloration[i]);	    
    }
    
}

int copySolution(Instance* instance, Solution* solution, SolutionValue value, Solution** destSolution, SolutionValue* destValue)
{
    if (*destSolution == NULL)
    {
	newSolution(destSolution, instance);
    }

    if (destValue->colorValues == NULL)
    {
	destValue->colorValues = malloc(sizeof(float) * instance->numColors);
    }
    
    
    memcpy((*destSolution)->coloration, solution->coloration, sizeof(uint) * instance->numVertices);
    memcpy((*destSolution)->numVertexPerColor, solution->numVertexPerColor, sizeof(uint) * instance->numColors);
    (*destSolution)->isFactible = solution->isFactible;
    (*destSolution)->numConflicts = solution->numConflicts;

    memcpy(destValue->colorValues, value.colorValues, sizeof(float) * instance->numColors);
    destValue->bestValue = value.bestValue;

    
    
    
    return 0;
}
