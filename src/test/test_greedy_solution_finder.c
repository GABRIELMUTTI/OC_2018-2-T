#include "../../include/test/test_greedy_solution_finder.h"

int testGreedySolutionFinder(const char* filepath)
{
    const float EPSILON = 1e-12;
    Instance* instance = NULL;

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }

    VertexWeight* sortedWeights = NULL;
    if (sortWeights(instance, &sortedWeights) != 0)
    {
	return TST_ERR_SORT_WEIGHTS;
    }


    SolutionValue solutionValue;
    solutionValue.bestValue = 0.0f;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);
    
    unsigned int i;
    for (i = 0; i < instance->numColors; i++)
    {
	solutionValue.colorValues[i] = 0.0f;
    }
    float alpha = 0.02f;
    
    Solution* solution = NULL;
    if (greedySolutionFinder(instance, &solution, &solutionValue, sortedWeights, alpha) != 0)
    {
	return TST_ERR_GREEDY_SOLUTION_FINDER;
    }
    
    printf("Solution Value: %f\n", solutionValue.bestValue);
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
	if (fabs(colorValues[i] - solutionValue.colorValues[i]) > EPSILON)
	{
	    return TST_ERR_WRONG_COLOR_VALUES;
	}
    }

    return 0;
}

int testMain()
{
    int status;
    status = testGreedySolutionFinder("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/tst_cmb01");

    return status;
}
