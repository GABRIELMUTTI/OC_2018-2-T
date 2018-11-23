#include "../include/grasp.h"

int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations)
{
    if (*solution == NULL)
    {
	*solution = malloc(sizeof(Solution));
	if (*solution == NULL) { return -3; }
    }
    
    Solution* currentSolution, *bestSolution;
    SolutionValue bestSolutionValue, currentSolutionValue;
    
    unsigned int iterationCounter = 0;
    do
    {
	if (greedySolutionFinder(instance, &currentSolution, &currentSolutionValue) != 0) { return -1; }
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

int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue)
{

    return 0;
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
