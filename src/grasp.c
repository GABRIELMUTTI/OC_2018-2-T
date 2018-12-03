#include "../include/grasp.h"

int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations, float alpha)
{
    clock_t start, end;
    double cpuTimeUsed;

    start = clock();

    
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

    newSolutionValue(&bestSolutionValue, instance);
    newSolutionValue(&currentSolutionValue, instance);
    
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

    unsigned int* sortedVertices = NULL;
    sortVerticesByDegree(instance, &sortedVertices);
    
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

    const unsigned int NUM_ELITES = 5;
    Solution** eliteSolutions = malloc(sizeof(Solution*) * NUM_ELITES);
    SolutionValue* eliteValues = malloc(sizeof(SolutionValue) * NUM_ELITES);
    unsigned int numElites = 0;

    for (i = 0; i < NUM_ELITES; i++)
    {
	eliteValues[i].colorValues = malloc(sizeof(float) * instance->numColors);
	newSolution(&eliteSolutions[i], instance);
    }
    
    if (greedySolutionFinder(instance, &bestSolution, &bestSolutionValue, sortedVertices, alpha) != 0) { return -1; }
    printf("Starting solution: %f <%d>\n", bestSolutionValue.bestValue, bestSolution->isFactible);
    float initialSolutionValue = bestSolutionValue.bestValue;
    unsigned int initialNumConflicts = countSolutionConflicts(instance, bestSolution);
   
    bestNumConflicts = countSolutionConflicts(instance, bestSolution);
    printf("Num Conflicts: %d\n", bestNumConflicts);
    unsigned int iterationCounter = 0;
    do
    {
	//printf("Iteration %d\n", iterationCounter);
	greedySolutionFinder(instance, &currentSolution, &currentSolutionValue, sortedVertices, alpha);
	unsigned int numConflicts = countSolutionConflicts(instance, currentSolution);
//	printf("Num Conflicts after greedy: %d\n", numConflicts);
//	printf(RED "After Greedy Value: %f <%d, %d>" RESET "\n", currentSolutionValue.bestValue, currentSolution->isFactible, countSolutionConflicts(instance, currentSolution));
	
	bestImprovementLocalSearch(instance, currentSolution, &currentSolutionValue, &numConflicts, maxDegree);
//	printf(GRN "After Local Value: %f <%d, %d>\n" RESET, currentSolutionValue.bestValue, currentSolution->isFactible, numConflicts);
	      
	// path relinking
	pathRelinking(instance, eliteSolutions, eliteValues, numElites, currentSolution, &currentSolutionValue, &numConflicts);
//	printf(MAG "After Path Relinking Value: %f <%d, %d>" RESET "\n", currentSolutionValue.bestValue, currentSolution->isFactible, countSolutionConflicts(instance, currentSolution));
	currentSolution->numConflicts = numConflicts;
	
	if ((!bestSolution->isFactible) || currentSolution->isFactible)
	{
	    if ((currentSolutionValue.bestValue < bestSolutionValue.bestValue && numConflicts <= bestNumConflicts) || (!bestSolution->isFactible && numConflicts < bestNumConflicts))
	    {
		copySolution(instance, currentSolution, currentSolutionValue, &bestSolution, &bestSolutionValue);
		bestNumConflicts = numConflicts;
	
		
		printf("Found better: %f <%d>, numConflicts: %d" RESET "\n", bestSolutionValue.bestValue, bestSolution->isFactible, bestNumConflicts);
	    }

	    if (numElites < NUM_ELITES)
	    {
		copySolution(instance, currentSolution, currentSolutionValue, &eliteSolutions[numElites], &eliteValues[numElites]);
		numElites++;
	    }
	    else
	    {
		uint biggestConflicts = eliteSolutions[0]->numConflicts;
		uint eliteIndex = 0;
		for (i = 1; i < NUM_ELITES; i++)
		{
		    float currentEliteConflicts = eliteSolutions[i]->numConflicts;
		    if (currentEliteConflicts > biggestConflicts)
		    {
			biggestConflicts = currentEliteConflicts;
			eliteIndex = i;
		    }
		}

//		printf("currentsol %d, biggest %d\n", currentSolution->numConflicts, biggestConflicts);
		if (currentSolution->numConflicts < biggestConflicts)
		{
		    copySolution(instance, currentSolution, currentSolutionValue, &eliteSolutions[eliteIndex], &eliteValues[eliteIndex]);
		}
		else
		{
		    float biggestValue = eliteValues[0].bestValue;
		    eliteIndex = 0;
		    uint biggestConflicts = eliteSolutions[0]->numConflicts;
		    for (i = 1; i < NUM_ELITES; i++)
		    {
			float currentEliteValue = eliteValues[i].bestValue;
			if (eliteSolutions[i]->numConflicts >= biggestConflicts || (eliteSolutions[i]->numConflicts >= biggestConflicts && currentEliteValue > biggestValue))
			{
			    biggestValue = currentEliteValue;
			    biggestConflicts = eliteSolutions[i]->numConflicts;
			    eliteIndex = i;
			}
		    }

		    if (currentSolutionValue.bestValue < biggestValue && biggestConflicts > currentSolution->numConflicts)
		    {
			copySolution(instance, currentSolution, currentSolutionValue, &eliteSolutions[eliteIndex], &eliteValues[eliteIndex]);
		    }
		}
		

	    }
	}


	if (iterationCounter % 100 == 0)
	{
	    printf("Iteration: %d\n", iterationCounter);
	}
	
	iterationCounter++;

	end = clock();
	cpuTimeUsed = (end - start) / CLOCKS_PER_SEC;

	if (cpuTimeUsed >= 1800)
	{
	    break;
	}
	
    } while(iterationCounter < numIterations);
    
    copySolution(instance, bestSolution, bestSolutionValue, solution, value);
    printf("Final solution value: %f <%d %d>\n", value->bestValue, (*solution)->isFactible, bestSolution->isFactible);
    printf("Initial solution value: %f, numConflicts: %d\n", initialSolutionValue, initialNumConflicts);

    free(bestSolutionValue.colorValues);
    free(currentSolutionValue.colorValues);
    
    return 0;
}

int sortVerticesByDegree(Instance* instance, unsigned int** sortedVertices)
{
    if (*sortedVertices == NULL)
    {
	*sortedVertices = malloc(sizeof(unsigned int) * instance->numVertices);
	if (*sortedVertices == NULL) { return -1; }
    }

    unsigned int degrees[instance->numVertices];
    unsigned int* sortingArray = *sortedVertices; 
        
    unsigned int i, j;
    for (i = 0; i < instance->numVertices; i++)
    {
	sortingArray[i] = i;
	degrees[i] = 0;
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (instance->graph[i][j] == 1 && i != j)
	    {
		degrees[i]++;
	    }
	}
    }

    for (i = 0; i < instance->numVertices; i++)
    {
	int biggestVertex = sortingArray[i];
	int biggestDegree = degrees[biggestVertex];
	int biggestIndex = i;
	
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (degrees[sortingArray[j]] > biggestDegree)
	    {
		biggestDegree = degrees[sortingArray[j]];
		biggestVertex = sortingArray[j];
		biggestIndex = j;
	    }
	}

	sortingArray[biggestIndex] = sortingArray[i];
	sortingArray[i] = biggestVertex;

	
    }
    
    return 0;
}


