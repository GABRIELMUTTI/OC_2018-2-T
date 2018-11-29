#include "../include/greedy.h"

int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue, float alpha)
{
    if (*solution == NULL)
    {
	if(newSolution(solution, instance) != 0) { return -1; }
    }

    (*solution)->isFactible = 1;
    
    uint chosenVertices[instance->numVertices];
    uint i;
    for (i = 0; i < instance->numVertices; i++)
    {
	(*solution)->coloration[i] = -1;
	chosenVertices[i] = 0;
    }

    for (i = 0; i < instance->numColors; i++)
    {
	(*solution)->numVertexPerColor[i] = 0;
	solutionValue->colorValues[i] = 0.0f;
    }

    solutionValue->bestValue = 0.0f;
    
    uint numChosenVertices = 0;
    while (numChosenVertices < instance->numVertices)
    {
	uint vertex, color, conflict;

	greedyChooseVertex(instance, *solution, chosenVertices, numChosenVertices, &vertex, &color, &conflict, alpha);

	(*solution)->coloration[vertex] = color;
	(*solution)->isFactible *= !conflict;
	(*solution)->numVertexPerColor[color] += 1;
	solutionValue->colorValues[color] += instance->weights[vertex];
		
	chosenVertices[vertex] = 1;
	numChosenVertices++;
    }

    float biggestValue = solutionValue->colorValues[0];
    for (i = 1; i < instance->numColors; i++)
    {
	float colorValue = solutionValue->colorValues[i];
	
	if (colorValue > biggestValue)
	{
	    biggestValue = colorValue;
	}
    }

    solutionValue->bestValue = biggestValue;
        
    return 0;
}


void greedyChooseVertex(Instance* instance, Solution* solution, uint* chosenVertices, uint numChosenVertices, uint* vertex, uint* color, uint* conflict, float alpha)
{
    uint rclSize = (1 - alpha) * (instance->numVertices - numChosenVertices);
    if (rclSize == 0)
    {
	rclSize = 1;
    }

    uint rclVertex[rclSize];
    uint rclColor[rclSize];
    uint rclConflicts[rclSize];

    constructRcl(instance, solution, chosenVertices, rclVertex, rclColor, rclConflicts, rclSize);
     
    int randomIndex = rand() % rclSize;

    *vertex = rclVertex[randomIndex];
    *color = rclColor[randomIndex];
    *conflict = rclConflicts[randomIndex];
 }

void constructRcl(Instance* instance, Solution* solution, uint* chosenVertices, uint* rclVertex, uint* rclColor, uint* rclConflict,  uint rclSize)
{
    uint rclCounter = 0;
    
    uint i, j, k;
    for (i = 0; i < instance->numVertices; i++)
    {
	if (chosenVertices[i] != 1)
	{
	    uint numNeighbours;
	    uint* neighboursColor = NULL;
	    uint* neighbours = NULL;
	    getVertexNeighbours(instance, solution, i, &neighbours, &neighboursColor, &numNeighbours);

	    int colorChosen = 0;
	    for (j = 0; j < instance->numColors; j++)
	    {
		int colorConflict = 0;
		for (k = 0; k < numNeighbours; k++)
		{
		    if (neighboursColor[k] == j)
		    {
			colorConflict = 1;
			break;
		    }
		}

		if (!colorConflict)
		{
		    rclVertex[rclCounter] = i;
		    rclColor[rclCounter] = j;
		    rclConflict[rclCounter] = 0;

		    rclCounter++;

		    if (rclCounter >= rclSize) { free(neighbours); free(neighboursColor); return; }
		    
		    colorChosen = 1;
		    break;
		}
	    }

	    if (!colorChosen)
	    {
		rclVertex[rclCounter] = i;
		rclColor[rclCounter] = 0;
		rclConflict[rclCounter] = 1;
		    
		rclCounter++;

		if (rclCounter >= rclSize) { free(neighbours); free(neighboursColor); return; }
		
	    }

	    free(neighbours);
	    free(neighboursColor);
	}
    }
}

