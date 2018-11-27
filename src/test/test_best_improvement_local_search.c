#include "../../include/test/test_best_improvement_local_search.h"

int testBestImprovementLocalSearch(const char* filepath)
{
    const float EPSILON = 1e-4;
    Instance* instance = NULL;

    time_t seed = 1;
    srand(time(&seed));

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

    if (bestImprovementLocalSearch(instance, solution, &solutionValue) != 0)
    {
	return TST_ERR_BEST_IMPROVEMENT_LOCAL_SEARCH;
    }

    // Checks if the color values are valid.
    float colorValues[instance->numColors];
    for (i = 0; i < instance->numColors; i++)
    {
	colorValues[i] = 0;
    }

    for (i = 0; i < instance->numVertices; i++)
    {
	colorValues[solution->coloration[i]] += instance->weights[i];
    }

    for (i = 0; i < instance->numColors; i++)
    {
	if (colorValues[i] != 0.0f && fabs(solutionValue.colorValues[i] - colorValues[i]) / colorValues[i] > EPSILON)
	{
	    return TST_ERR_WRONG_COLOR_VALUES;
	}
    }

    // Checks if the heaviest color value is valid.
    unsigned int heaviestColor = 0;
    for (i = 1; i < instance->numColors; i++)
    {
	if (solutionValue.colorValues[i] > solutionValue.colorValues[heaviestColor])
	{
	    heaviestColor = i;
	}
    }

    if (fabs(solutionValue.colorValues[heaviestColor] - solutionValue.bestValue) > EPSILON)
    {
	return TST_ERR_WRONG_BEST_VALUE;
    }
    
    return 0;
}
