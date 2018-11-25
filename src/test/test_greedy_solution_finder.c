#include "../../include/test/test_greedy_solution_finder.h"

int testGreedySolutionFinder(const char* filepath)
{
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
    
    printf("Soltution Value: %f\n", solutionValue.bestValue);

    
    return 0;
}

int main()
{
    int status;
    status = testGreedySolutionFinder("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb01");

    return status;
}
