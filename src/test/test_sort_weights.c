#include "../../include/test/test_sort_weights.h"

int testSortWeights()
{
    const float EPSILON = 1e-10;
    
    Instance* instance;

    if (loadInstance(&instance, "home/Documents/ufrgs/courses/oc/trab/instances/cmb01") != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }

    VertexWeight* weights;

    if (sortWeights(instance, &weights) != 0)
    {
	return TST_ERR_SORT_WEIGHTS;
    }

    // Checks if its sorted.
    unsigned int i;
    for (i = 0; i < instance->numVertices - 1; i++)
    {
	if (weights[i].weight < weights[i + 1].weight)
	{
	    return TST_ERR_NOT_SORTED;
	}

	if (fabs(weights[i].weight - instance->weights[weights[i].vertex]) > EPSILON)
	{
	    return TST_ERR_WRONG_VERTEX_WEIGHT;
	}
    }
    
    return 0;
}

int main()
{
    return testSortWeights();
}
