#include "../../include/test/test_best_improvement_local_search.h"

int testBestImprovementLocalSearch(const char* filepath)
{
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

    
    return 0;
}

int main()
{

    testBestImprovementLocalSearch("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/tst_cmb02");
    
    return 0;
}
