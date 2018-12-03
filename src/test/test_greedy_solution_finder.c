#include "../../include/test/test_greedy_solution_finder.h"

int testGreedySolutionFinder(const char* filepath)
{
    srand(time(NULL));
    const float EPSILON = 1e-5;
    Instance* instance = NULL;

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }


    SolutionValue solutionValue;
    solutionValue.bestValue = 0.0f;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);
    
    unsigned int i;
    for (i = 0; i < instance->numColors; i++)
    {
	solutionValue.colorValues[i] = 0.0f;
    }
    float alpha = 0.5f;
    
    Solution* solution = NULL;
    greedySolutionFinder(instance, &solution, &solutionValue, alpha);

    
    printf("Solution Value: %f <%d>\n", solutionValue.bestValue, solution->isFactible);

    unsigned int numConflicts = 0;
    unsigned int j;
    for (i = 0; i < instance->numVertices; i++)
    {
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (instance->graph[i][j] == 1 && solution->coloration[i] == solution->coloration[j])
	    {
		numConflicts++;
	    }
	}
    }
    
    printf("Num Conflicts: %d\n", numConflicts);
    for (i = 0; i < instance->numColors; i++)
    {
	printf("Color %d: %f\n", i, solutionValue.colorValues[i]);
    }

    // Checks if the color values in the solution are valid.
    float colorValues[instance->numColors];
    for (i = 0; i < instance->numColors; i++)
    {
	colorValues[i] = 0.0f;
    }

    for (i = 0; i < instance->numVertices; i++)
    {
	colorValues[solution->coloration[i]] += instance->weights[i];
    }

    for (i = 0; i < instance->numColors; i++)
    {
	if (solutionValue.colorValues[i] != 0.0f && fabs((colorValues[i] - solutionValue.colorValues[i]) / solutionValue.colorValues[i]) > EPSILON)
	{
	    return TST_ERR_WRONG_COLOR_VALUES;
	}
    }

    bestImprovementLocalSearch(instance, solution, &solutionValue, 0, 0);

    numConflicts = 0;
    for (i = 0; i < instance->numVertices; i++)
    {
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (instance->graph[i][j] == 1 && solution->coloration[i] == solution->coloration[j])
	    {
		numConflicts++;
	    }
	}
    }

    printf("Num Conflicts After Improvement: %d\n", numConflicts);

    tryToImprove(instance, solution);

    unsigned int* neighbours = NULL;
    unsigned int* colors = NULL;
    unsigned int numNeighbours;
    
  
    unsigned int maxDegree = 0;
    for (i = 0; i < instance->numVertices; i++)
    {
	getVertexNeighbours(instance, solution, i, &neighbours, &colors, &numNeighbours);

	if (numNeighbours > maxDegree)
	{
	    maxDegree = numNeighbours;
	}
	
    }

    printf("max degree: %d\n", maxDegree);
    
    return 0;
}

int tmain()
{
    testGreedySolutionFinder("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb01");

    return 0;
}


void tryToImprove(Instance* instance, Solution* solution)
{
    unsigned int i, j;
    unsigned int numConflicts;
    
    for (i = 0; i < instance->numVertices; i++)
    {
	
	unsigned int vertexColor = solution->coloration[i];
	unsigned int numConflicts = countConflicts(instance, solution, i);
	
	for (j = 0; j < instance->numColors; j++)
	{
	    if (vertexColor != j)
	    {
		solution->coloration[i] = j;
		if (countConflicts(instance, solution, i) >= numConflicts)
		{
		    solution->coloration[i] = vertexColor;
		}
		else
		{
		    break;
		}
	       
	    }
	}

    }

    numConflicts = 0;
    for (i = 0; i < instance->numVertices; i++)
    {
	for (j = i + 1; j < instance->numVertices; j++)
	{
	    if (instance->graph[i][j] == 1 && solution->coloration[i] == solution->coloration[j])
	    {
		numConflicts++;
		//printf("conflicting vertex: %d\n", j);
		//printNeighbourColors(instance, solution, i);
	    }
	}
    }
    printf("Num Conflicts After Checkage: %d\n", numConflicts);
}


void printNeighbourColors(Instance* instance, Solution* solution, unsigned int vertex)
{
    unsigned int* neighbours = NULL;
    unsigned int* colors = NULL;
    unsigned int numNeighbours;
    
    getVertexNeighbours(instance, solution, vertex, &neighbours, &colors, &numNeighbours);

    printf("Vertex %d color: %d\n", vertex, solution->coloration[vertex]);
    
    unsigned int i;
    for (i = 0; i < numNeighbours; i++)
    {
	printf("Neighbour %d color: %d\n", neighbours[i], colors[i]);
    }
}
