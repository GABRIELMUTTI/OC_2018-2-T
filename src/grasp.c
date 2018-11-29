#include "../include/grasp.h"

int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations, float alpha)
{
    if (*solution == NULL)
    {
	if (newSolution(solution, instance) != 0) { return -1; }
    }
    
    Solution* currentSolution = NULL;
    Solution* bestSolution = NULL;
    unsigned int bestNumConflicts = 0;
 
    SolutionValue bestSolutionValue, currentSolutionValue;

    newSolution(&bestSolution, instance);
    newSolution(&currentSolution, instance);
    
    bestSolutionValue.colorValues = malloc(sizeof(float) * instance->numColors);
    currentSolutionValue.colorValues = malloc(sizeof(float) * instance->numColors);

    unsigned int i, j;
    for (i = 0; i < instance->numColors; i++)
    {
	bestSolutionValue.colorValues[i] = 0.0f;
	currentSolutionValue.colorValues[i] = 0.0f;
    }
    
    bestSolutionValue.bestValue = 0.0f;
    currentSolutionValue.bestValue = 0.0f;


    unsigned int maxDegree = 0;
    for (i = 0; i < instance->numVertices; i++)
    {
	unsigned int degree = 0;
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (instance->graph[i][j] == 1)
	    {
		degree++;
	    }
	}

	if (degree > maxDegree)
	{
	    maxDegree = degree;
	}
    }
    
    if (greedySolutionFinder(instance, &bestSolution, &bestSolutionValue, alpha) != 0) { return -1; }
    printf("Starting solution: %f <%d>\n", bestSolutionValue.bestValue, bestSolution->isFactible);
    //printf("Num Conflicts: %d\n", countSolutionConflicts(instance, bestSolution));
    bestNumConflicts = countSolutionConflicts(instance, *solution);
    unsigned int iterationCounter = 0;
    do
    {
	//printf("Iteration %d\n", iterationCounter);
	if (greedySolutionFinder(instance, &currentSolution, &currentSolutionValue, alpha) != 0) { return -1; }
	unsigned int numConflicts = countSolutionConflicts(instance, currentSolution);
	//	printf("Num Conflicts after greedy: %d\n", numConflicts);
	//	printf("After Greedy Value: %f <%d>\n", currentSolutionValue.bestValue, currentSolution->isFactible);
	
	if (bestImprovementLocalSearch(instance, currentSolution, &currentSolutionValue, &numConflicts, maxDegree)) { return -2; }
	//	printf("After Local Value: %f <%d>, numConflicts: %d\n", currentSolutionValue.bestValue, currentSolution->isFactible, numConflicts);
	
	if ((!bestSolution->isFactible) || currentSolution->isFactible)
	{
	    if ((currentSolutionValue.bestValue < bestSolutionValue.bestValue && numConflicts < bestNumConflicts) || (!bestSolution->isFactible && numConflicts < bestNumConflicts))
	    {
		memcpy(bestSolution->coloration, currentSolution->coloration, sizeof(unsigned int) * instance->numVertices);
		memcpy(bestSolution->numVertexPerColor, currentSolution->numVertexPerColor, sizeof(unsigned int) * instance->numColors);

		memcpy(bestSolutionValue.colorValues, currentSolutionValue.colorValues, sizeof(float) * instance->numColors);
		bestSolutionValue.bestValue = currentSolutionValue.bestValue;
		bestSolution->isFactible = currentSolution->isFactible;
		bestNumConflicts = numConflicts;
		
		printf("Found better: %f <%d>\n", bestSolutionValue.bestValue, bestSolution->isFactible);
	    }
	}

	if (iterationCounter % 100 == 0)
	{
	    printf("Iteration: %d\n", iterationCounter);
	}
	
	iterationCounter++;
    } while(iterationCounter < numIterations);
    
    memcpy((*solution)->coloration, bestSolution->coloration, sizeof(unsigned int) * instance->numVertices);
    memcpy((*solution)->numVertexPerColor, bestSolution->numVertexPerColor, sizeof(unsigned int) * instance->numColors);
    (*solution)->isFactible = bestSolution->isFactible;
    
    memcpy(value->colorValues, bestSolutionValue.colorValues, sizeof(float) * instance->numColors);
    value->bestValue = bestSolutionValue.bestValue;

    (*solution)->isFactible = checkFactibility(instance, *solution);
    printf("Final solution value: %f <%d %d>\n", value->bestValue, (*solution)->isFactible, bestSolution->isFactible);

    free(bestSolutionValue.colorValues);
    free(currentSolutionValue.colorValues);
    
    return 0;
}
