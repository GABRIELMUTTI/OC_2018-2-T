#include "../include/local_search.h"

int bestImprovementLocalSearch(Instance* instance, Solution* solution, SolutionValue* solutionValue, unsigned int* numConflicts, unsigned int maxDegree)
{
    unsigned int neighbours[maxDegree];
    unsigned int neighboursColor[maxDegree];
    unsigned int neighboursColorCount[instance->numColors];
    int local_numConflicts = *numConflicts;
    const unsigned int NUM_CHANGES = 2;
    const unsigned int NUM_NEUTRAL_CHANGES = NUM_CHANGES - 1;

    int haveImproved;
    do
    {
	unsigned int numChangesFound = 0;
	unsigned int numNeutralChangesFound = 0;
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

		    float inColorValue = solutionValue->colorValues[j] + instance->weights[i];
		    float outColorValue = solutionValue->colorValues[vertexColor] - instance->weights[i];
		    
		    if (solution->isFactible)
		    {
			if (numNeighbourConflicts == 0)
			{
			    int isHeaviestColor = 1;
			    for (k = 0; k < instance->numColors; k++)
			    {
				if (k == vertexColor)
				{
				    if (inColorValue < outColorValue)
				    {
					isHeaviestColor = 0;
					break;
				    }
				}
				else if (inColorValue < solutionValue->colorValues[k])
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
				solution->numVertexPerColor[j]++;
				solution->numVertexPerColor[vertexColor]--;
			    
				haveImproved = 1;
				numChangesFound++;
				break;
			    }
			}
		    }
		    else
		    {
			if (numNeighbourConflicts < numVertexConflicts)
			{
			    local_numConflicts -= numVertexConflicts;
			    local_numConflicts += numNeighbourConflicts;

			    solutionValue->colorValues[vertexColor] = outColorValue;
			    solutionValue->colorValues[j] = inColorValue;
			    solution->numVertexPerColor[j]++;
			    solution->numVertexPerColor[vertexColor]--;
			    
			    haveImproved = 1;
			    numChangesFound++;
			    break;
			}
			else if (numChangesFound < NUM_NEUTRAL_CHANGES && numNeighbourConflicts == numVertexConflicts && solution->numVertexPerColor[j] > solution->numVertexPerColor[vertexColor])
			{
//			    printf("vertex: %d %d -> %d\n", i, vertexColor, j);
			    
			    local_numConflicts -= numVertexConflicts;
			    local_numConflicts += numNeighbourConflicts;

			    solutionValue->colorValues[vertexColor] = outColorValue;
			    solutionValue->colorValues[j] = inColorValue;
			    solution->numVertexPerColor[j]++;
			    solution->numVertexPerColor[vertexColor]--;
			    
			    numChangesFound++;
			    numNeutralChangesFound++;

			    if (numNeutralChangesFound - numChangesFound > 0)
			    {
				haveImproved = 1;
			    }
			    
			    break;	

			}
		    }
		
		}

		if (haveImproved && numChangesFound >= NUM_CHANGES)
		{
		    break;
		}
		else
		{
		    solution->coloration[i] = vertexColor;
		}
	    }
		
	    if (haveImproved && numChangesFound >= NUM_CHANGES)
	    {
		break;
	    }
	}

//	printf("numchangesfound: %d, numneutralchangesfound: %d\n", numChangesFound, numNeutralChangesFound);

	if (local_numConflicts == 0)
	{
	    solution->isFactible = 1;
	    updateSolutionValue(instance, solution, solutionValue);
	}
	
    } while (haveImproved);
    

    *numConflicts = local_numConflicts;
    
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


void updateSolutionValue(Instance* instance, Solution* solution, SolutionValue* solutionValue)
{
    float heaviestColorValue = solutionValue->colorValues[0];
    
    unsigned int i;
    for (i = 1; i < instance->numColors; i++)
    {
	if (solutionValue->colorValues[i] > heaviestColorValue)
	{
	    heaviestColorValue = solutionValue->colorValues[i];
	}
    }

    solutionValue->bestValue = heaviestColorValue;
}
