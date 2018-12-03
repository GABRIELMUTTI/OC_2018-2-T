#include "../include/path_relinking.h"

int pathRelinking(Instance* instance, Solution** eliteSolutions, SolutionValue* eliteValues, uint numElites, Solution* solution, SolutionValue* solutionValue, uint* out_numConflicts)
{
    Solution* currentSolution = NULL;
    SolutionValue currentValue;

    Solution* bestSolution = NULL;
    SolutionValue bestSolutionValue;

    Delta* deltas = NULL;
    uint numDeltas;

    newSolutionValue(&currentValue, instance);
    newSolutionValue(&bestSolutionValue, instance);

    int bestNumConflicts = *out_numConflicts;
    int currentNumConflicts = bestNumConflicts;

    
    copySolution(instance, solution, *solutionValue, &bestSolution, &bestSolutionValue);

    uint foundBetter = 0;
    uint i;
    for (i = 0; i < numElites; i++)
    {
	// Copies the original solution to the current solution.
	copySolution(instance, solution, *solutionValue, &currentSolution, &currentValue);

	getDelta(instance, eliteSolutions[i], currentSolution, &deltas, &numDeltas);
	currentNumConflicts = solution->numConflicts;
//	printf("cunne: %d\n", currentNumConflicts);

	uint j;
	for (j = 0; j < numDeltas; j++)
	{
	    uint vertex = deltas[j].vertex;
	    uint inColor = deltas[j].color;
	    uint outColor = currentSolution->coloration[vertex];

	    uint oldNumConflicts = countConflicts(instance, solution, vertex);
	    
	    currentSolution->coloration[vertex] = inColor;
	    float inColorValue = currentValue.colorValues[inColor] + instance->weights[vertex];
	    float outColorValue = currentValue.colorValues[outColor] - instance->weights[vertex];

	    currentValue.colorValues[inColor] = inColorValue;
	    currentValue.colorValues[outColor] = outColorValue;

	    float heaviestColorValue = currentValue.colorValues[0];
	    uint k;
	    for (k = 1; k < instance->numColors; k++)
	    {
		float currentColorValue = currentValue.colorValues[k];
		if (currentColorValue > heaviestColorValue)
		{
		    heaviestColorValue = currentColorValue;
		}
	    }

	    currentValue.bestValue = heaviestColorValue;

	    uint numConflicts = countConflicts(instance, currentSolution, vertex);
	    currentNumConflicts += numConflicts - oldNumConflicts;
	    
	    if (currentNumConflicts < bestNumConflicts)
	    {

		
		if (currentNumConflicts == 0)
		{
		    currentSolution->isFactible = 1;
		    printf("factible??? %d\n", countSolutionConflicts(instance, currentSolution));
		}

		*bestSolution = *currentSolution;
		bestSolutionValue = currentValue;
		bestNumConflicts = currentNumConflicts;

		foundBetter = 1;
	    }
	    else
	    {
		if (solution->isFactible && currentSolution->isFactible)
		{
		    if (currentValue.bestValue < solutionValue->bestValue)
		    {
			*bestSolution = *currentSolution;
			bestSolutionValue = currentValue;
			bestNumConflicts = currentNumConflicts;

			foundBetter = 1;
		    }
		}
	    }
	}

	if (foundBetter)
	{
	    currentSolution = NULL;
	    currentValue.colorValues = NULL;
//	    printf("Found better in relinking: %f <%d, %d>!\n", bestSolutionValue.bestValue, bestSolution->isFactible, bestNumConflicts);
	    
	}
    }


    free(deltas);

    copySolution(instance, bestSolution, bestSolutionValue, &solution, solutionValue);

    if (currentSolution != NULL)
    {
	destroySolution(currentSolution);
    }

    if (currentValue.colorValues != NULL)
    {
	free(currentValue.colorValues);
    }

    *out_numConflicts = bestNumConflicts;
    
    return 0;
}

int getDelta(Instance* instance, Solution* s1, Solution* s2, Delta** out_deltas, uint* out_numDeltas)
{
    if (*out_deltas == NULL)
    {
	*out_deltas = malloc(sizeof(Delta) * instance->numVertices);
    }

    *out_numDeltas = 0;
    
    uint i;
    for (i = 0; i < instance->numVertices; i++)
    {
	uint s1Color = s1->coloration[i];
	uint s2Color = s2->coloration[i];

	if (s1Color != s2Color)
	{
	    (*out_deltas)[*out_numDeltas].vertex = i;
	    (*out_deltas)[*out_numDeltas].color = s1Color;
	    (*out_numDeltas)++;
	}
    }
	    
    return 0;
}

