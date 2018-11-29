#include "../include/local_search.h"

int bestImprovementLocalSearch(Instance* instance, Solution* solution, SolutionValue* solutionValue, unsigned int numConflicts, unsigned int maxDegree)
{
    unsigned int neighbours[maxDegree];
    unsigned int neighboursColor[maxDegree];
    unsigned int neighboursColorCount[instance->numColors];
    
    int haveImproved;
    do
    {
	haveImproved = 0;

	unsigned int i, j, k;
	for (i = 0; i < instance->numVertices; i++)
	{
	    unsigned int vertexColor = solution->coloration[i];
	    unsigned int numNeighbours;
	    unsigned int numVertexConflicts;

	    getVertexNeighboursInfo(instance, solution, i, neighbours, neighboursColor, neighboursColorCount, &numVertexConflicts, &numNeighbours);
	    	    
	    for (j = 0; j < instance->numColors; j++)
	    {
		
		if (vertexColor != j)
		{
		    solution->coloration[i] = j;
		    unsigned int numNeighbourConflicts = neighboursColorCount[j];
		    
		    if (solution->isFactible)
		    {
			if (numNeighbourConflicts == 0)
			{
			    float inColorValue = solutionValue->colorValues[j] + instance->weights[i];
			    float outColorValue = solutionValue->colorValues[vertexColor] - instance->weights[i];

			    int isHeaviestColor = 1;
			    for (k = 0; k < instance->numColors; k++)
			    {
				if (inColorValue < solutionValue->colorValues[k])
				{
				    isHeaviestColor = 0;
				    break;
				}
			    }

			    if (isHeaviestColor && inColorValue < solutionValue->bestValue)
			    {
				solutionValue->colorValues[vertexColor] = outColorValue;
				solutionValue->colorValues[j] = inColorValue;
				solutionValue->bestValue = inColorValue;

				haveImproved = 1;
				break;
			    }
			    else
			    {
				solution->coloration[i] = vertexColor;
			    }
			}
		    }
		    else
		    {
			if (numNeighbourConflicts >= numVertexConflicts)
			{
			    solution->coloration[i] = vertexColor;
			}
			else
			{
			    numConflicts -= numVertexConflicts;
			    numConflicts += numNeighbourConflicts;
			    haveImproved = 1;
			    break;
			}	
		    }
		
		}

		if (haveImproved)
		{
		    break;
		}
	    }
		
	    if (haveImproved)
	    {
		break;
	    }
	    
	}

	if (numConflicts == 0)
	{
	    solution->isFactible = 1;
	}
	
    } while (haveImproved);
    
    
    return 0;
}

int findNeighbours(Instance* instance, Solution* solution, Neighbour** neighbours, unsigned int* numNeighbours)
{
    unsigned int local_numNeighbours = 0;
   
    unsigned int i, j;
    for (i = 0; i < instance->numColors; i++)
    {
	for (j = 0; j < instance->numColors; j++)
	{
	    if (i != j)
	    {	
		local_numNeighbours += solution->numVertexPerColor[j];	    
	    }
	}
    }
    
    Neighbour* local_neighbours = malloc(sizeof(Neighbour) * local_numNeighbours);
    if (local_neighbours == NULL) { return -1; }

    unsigned int neighboursCount = 0;
    for (i = 0; i < instance->numColors; i++)
    {
	for (j = 0; j < instance->numVertices; j++)
	{
	    if (solution->coloration[j] != i)
	    {
		local_neighbours[neighboursCount].inColor = i;
		local_neighbours[neighboursCount].outColor = solution->coloration[j];
		local_neighbours[neighboursCount].vertex = j;
		neighboursCount++;
	    }
	}
    }

    *neighbours = local_neighbours;
    *numNeighbours = local_numNeighbours;
    
    return 0;
}


// if factible and neighbour factible -> factible
// if factible and neighbour unfactible -> unfactible
// if unfactible and neighbour factible and numConflicts == this neighbours conflicts-> FACTIBLE!
// if unfactible and neighbour unfactible -> unfactible

int checkNeighbourFactible(Instance* instance, Solution* solution, Neighbour neighbour, unsigned int numConflicts)
{
    solution->coloration[neighbour.vertex] = neighbour.inColor;
    int vertexFactibility = checkVertexFactibility(instance, solution, neighbour.vertex);

    if (solution->isFactible && vertexFactibility) { return 1; }
    if (solution->isFactible && !vertexFactibility) { return 0; }
    if (!solution->isFactible && !vertexFactibility) { return 0; }

    solution->coloration[neighbour.vertex] = neighbour.outColor;
    if (countConflicts(instance, solution, neighbour.vertex) == numConflicts)
    {
	solution->coloration[neighbour.vertex] = neighbour.inColor;
	if (countConflicts(instance, solution, neighbour.vertex) == 0)
	{
	    return 1;
	}
    }

    return 0;
}
