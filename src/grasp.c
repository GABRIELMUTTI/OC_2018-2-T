#include "../include/grasp.h"

int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations, float alpha)
{
    if (*solution == NULL)
    {
	if (newSolution(solution, instance) != 0) { return -1; }
    }
    
    Solution* currentSolution, *bestSolution;
    SolutionValue bestSolutionValue, currentSolutionValue;

    VertexWeight* sortedWeights;
    if (sortWeights(instance, &sortedWeights) != 0) { return -1; }
    
    unsigned int iterationCounter = 0;
    do
    {
	if (greedySolutionFinder(instance, &currentSolution, &currentSolutionValue, sortedWeights, alpha) != 0) { return -1; }
	if (bestImprovementLocalSearch(instance, currentSolution, &currentSolutionValue)) { return -2; }

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

int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue, VertexWeight* sortedWeights, float alpha)
{
    if (*solution == 0)
    {
	if (newSolution(solution, instance) != 0) { return -1; }
    }

    // Initializes numVertexPerColor.
    unsigned int i;
    for (i = 0; i < instance->numColors; i++)
    {
	(*solution)->numVertexPerColor[i] = 0;
    }
   
    // Initializer chosenVertices.
    unsigned int chosenVertices[instance->numVertices];
    for (i = 0; i < instance->numVertices; i++)
    {
	chosenVertices[i] = 0;
    }

    unsigned int vertexCounter = 0;
    while (vertexCounter < instance->numVertices)
    {
	unsigned int color;
	unsigned int vertex;
	greedyChooseVertex(instance, sortedWeights, chosenVertices, vertexCounter, &vertex, &color, solutionValue, alpha);
	
	chosenVertices[vertex] = 1;
	colorVertex(*solution, vertex, color);

	solutionValue->colorValues[color] += instance->weights[vertex];
	(*solution)->numVertexPerColor[color]++;

	vertexCounter++;
    }

    solutionValue->bestValue = solutionValue->colorValues[0];
    for (i = 1; i < instance->numColors; i++)
    {
	if (solutionValue->colorValues[i] > solutionValue->bestValue)
	{
	    solutionValue->bestValue = solutionValue->colorValues[i];
	}
    }
    
    return 0;
}

int greedyChooseVertex(Instance* instance, VertexWeight* sortedWeights, unsigned int* chosenVertices, unsigned int numChosenVertices, unsigned int* vertex, unsigned int* color, SolutionValue* value, float alpha)
{
    unsigned int sizeRCL = alpha * (instance->numVertices - numChosenVertices);
    if (sizeRCL == 0)
    {
	sizeRCL = 1;
    }

    unsigned int rcl[sizeRCL];
    unsigned int rclCounter = 0;
    unsigned int nextVertexIndex = 0;
       
    // Finds the heaviest vertex.
    while (rclCounter < sizeRCL)
    {
	unsigned int i;
	for (i = nextVertexIndex; i < instance->numVertices; i++)
	{
	    if (chosenVertices[sortedWeights[i].vertex] != 1)
	    {
		nextVertexIndex = i + 1;
		rcl[rclCounter] = sortedWeights[i].vertex;
		break;
	    }
	}
	
	rclCounter++;
    }

    // Finds the lightest color.
    unsigned int lightestColor = 0;
    unsigned int i;
    for (i = 1; i < instance->numColors; i++)
    {
	if (value->colorValues[i] < value->colorValues[lightestColor])
	{
	    lightestColor = i;
	}
    }
    
    
    unsigned int randomIndex = rand() % sizeRCL;

    *vertex = rcl[randomIndex];
    *color = lightestColor;
        
    return 0;
}

int bestImprovementLocalSearch(Instance* instance, Solution* solution, SolutionValue* solutionValue)
{
    unsigned int numNeighbours;
    Neighbour* neighbours;
    
    Neighbour bestNeighbour;

    unsigned int i, j;
    int haveImproved;

    do
    {
	if (findNeighbours(instance, solution, &neighbours, &numNeighbours) != 0) { return -1; }
	
	float neighbourInColorValue, neighbourOutColorValue;
	float bestNeighbourInColorValue, bestNeighbourOutColorValue;
	haveImproved = 0;
	for (i = 0; i < numNeighbours; i++)
	{
	    unsigned int changedVertex = neighbours[i].vertex;
	    unsigned int inColor = neighbours[i].inColor;
	    unsigned int outColor = neighbours[i].outColor;
		   
	    neighbourOutColorValue = solutionValue->colorValues[outColor] - instance->weights[changedVertex];
	    neighbourInColorValue = solutionValue->colorValues[inColor] + instance->weights[changedVertex];

	    float heaviestColorValue = -1.0f;
	    for (j = 0; j < instance->numColors; j++)
	    {
		float colorValue;
		if (j == inColor)
		{
		    colorValue = neighbourInColorValue;
		}
		else if (j == outColor)
		{
		    colorValue = neighbourOutColorValue;
		}
		else
		{
		    colorValue = solutionValue->colorValues[j];
		}

		if (colorValue > heaviestColorValue)
		{
		    heaviestColorValue = colorValue;
		}
	    }
	    
	    if (heaviestColorValue < solutionValue->bestValue)
	    {
		solutionValue->bestValue = heaviestColorValue;
		bestNeighbourInColorValue = neighbourInColorValue;
		bestNeighbourOutColorValue = neighbourOutColorValue;
		bestNeighbour = neighbours[i];
		
		haveImproved = 1;
	    }
	}

	if (haveImproved)
	{
	    solution->coloration[bestNeighbour.vertex] = bestNeighbour.inColor;
	    solutionValue->colorValues[bestNeighbour.outColor] = bestNeighbourOutColorValue;
	    solutionValue->colorValues[bestNeighbour.inColor] = bestNeighbourInColorValue;
	}

	
    } while(haveImproved);

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

int sortWeights(Instance* instance, VertexWeight** sortedWeights)
{
    if (*sortedWeights == NULL)
    {
	*sortedWeights = malloc(sizeof(VertexWeight) * instance->numVertices);
	if (*sortedWeights == NULL) { return -1; }
    }
    
    VertexWeight* sortingArray = *sortedWeights; 
        
    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	sortingArray[i].vertex = i;
	sortingArray[i].weight = instance->weights[i];
    }
    
    // Insertion sort (for now, eventually I’ll implement quicksort probably).
    unsigned int j;
    unsigned int heaviestIndex;
    VertexWeight heaviestVertexWeight;
    for (i = 0; i < instance->numVertices; i++)
    {
	heaviestVertexWeight = sortingArray[i];
	heaviestIndex = i;
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (sortingArray[j].weight > heaviestVertexWeight.weight)
	    {
		heaviestVertexWeight = sortingArray[j];
		heaviestIndex = j;
	    }
	}

	sortingArray[heaviestIndex] = sortingArray[i];
	sortingArray[i] = heaviestVertexWeight;
    }
    
    return 0;
}
