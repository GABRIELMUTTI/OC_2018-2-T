#include "../include/grasp.h"

int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations)
{
    if (*solution == NULL)
    {
	if (newSolution(solution, instance) != 0) { return -1; }
    }
    
    Solution* currentSolution, *bestSolution;
    SolutionValue bestSolutionValue, currentSolutionValue;

    float* sortedWeights = NULL;
    
    unsigned int iterationCounter = 0;
    do
    {
	if (greedySolutionFinder(instance, &currentSolution, &currentSolutionValue, sortedWeights) != 0) { return -1; }
	if (bestImprovementLocalSearch(instance, &currentSolution, &currentSolutionValue)) { return -2; }

	if (currentSolutionValue.bestValue < bestSolutionValue.bestValue)
	{
	    bestSolution = currentSolution;
	    bestSolutionValue = currentSolutionValue;
	}

	iterationCounter++;
    } while(iterationCounter < numIterations);
    
    *solution = bestSolution;
    *value = bestSolutionValue;
    
    return 0;
}

int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue, float* sortedWeights)
{
    if (*solution == 0)
    {
	if (newSolution(solution, instance) != 0) { return -1; }
    }

    unsigned int chosenVertexes[instance->numVertices];

    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	chosenVertexes[i] = 0;
    }
    
    unsigned int vertexCounter;
    while (vertexCounter < instance->numVertices)
    {
	unsigned int color;
	unsigned int vertex;
	greedyChooseVertex(instance, sortedWeights, chosenVertexes, &vertex, &color, solutionValue);
	
	chosenVertexes[vertex] = 1;
	colorVertex(*solution, vertex, color);
	
	vertexCounter++;
    }
    
    return 0;
}

unsigned int greedyChooseVertex(Instance* instance, float* sortedWeights, unsigned int* chosenVertices, unsigned int* vertex, unsigned int* color, SolutionValue* value)
{

    
}

int bestImprovementLocalSearch(Instance* instance, Solution** solution, SolutionValue* solutionValue)
{
    unsigned int numNeighbours;
    SolutionValue bestValue, neighbourValue;
    Neighbour* neighbours;
    Solution* bestSolution, *neighbour;
    // Need to implement deep copy.

    bestValue = *solutionValue;
    *bestSolution = **solution;
    
    int haveImproved = 1;
    unsigned int i;
    do
    {
	if (findNeighbours(instance, bestSolution, &neighbours, &numNeighbours) != 0) { return -1; }

	*neighbour = *bestSolution;
	neighbourValue = bestValue;
	for (i = 0; i < numNeighbours; i++)
	{
	    unsigned int changedVertex = neighbours[i].vertex;
	    unsigned int inColor = neighbours[i].inColor;
	    unsigned int outColor = neighbours[i].outColor;
	
	   
      	    neighbour->coloration[changedVertex] = inColor;
	    neighbourValue.colorValues[outColor] -= instance->weights[changedVertex];
	    neighbourValue.colorValues[inColor] += instance->weights[changedVertex];

	    if (neighbourValue.colorValues[inColor] < neighbourValue.bestValue)
	    {
		neighbourValue.bestValue = neighbourValue.colorValues[inColor];
	    }
	    
	    
	    if (neighbourValue.bestValue < bestValue.bestValue)
	    {
		colorVertex(bestSolution, changedVertex, inColor);
		bestValue = neighbourValue;
	    }
	}
		
    } while(haveImproved);

    *solutionValue = bestValue;
    *solution = bestSolution;
    
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
		local_numNeighbours += solution->numVertexPerColor[i] * solution->numVertexPerColor[j];
	    }
	}
    }
    
    
    Neighbour* local_neighbours = malloc(sizeof(Neighbour) * local_numNeighbours);
    if (local_neighbours == 0) { return -1; }

    for (i = 0; i < instance->numColors; i++)
    {
	for (j = 0; j < instance->numVertices; j++)
	{
	    if (solution->coloration[j] != i)
	    {
		Neighbour neighbour;
		neighbour.inColor = i;
		neighbour.outColor = solution->coloration[j];
		neighbour.vertex = j;
		
		local_neighbours[j] = neighbour;
	    }
	}
    }

    *neighbours = local_neighbours;
    *numNeighbours = local_numNeighbours;
    
    return 0;
}
