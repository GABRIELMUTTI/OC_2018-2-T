#include "../../include/test/test_sort_weights.h"

int testSortWeights(const char* filepath)
{
    const float EPSILON = 1e-10;
    
    Instance* instance = NULL;

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }

    VertexWeight* weights = NULL;

    //    if (sortWeights(instance, &weights) != 0)
    //{
    //	return TST_ERR_SORT_WEIGHTS;
    //}

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

	unsigned int j;
	int found = 0;
	for (j = 0; j < instance->numVertices; j++)
	{
	    if (fabs(instance->weights[i] - weights[j].weight) < EPSILON)
	    {
		found = 1;
	    }
	}

	if (!found)
	{
	    return TST_ERR_MISSING_WEIGHTS;
	}	
    }
    
    return 0;
}

int test_main()
{
    int status;
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb01");
    printf("Test result 1: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb02");
    printf("Test result 2: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb03");
    printf("Test result 3: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb04");
    printf("Test result 4: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb05");
    printf("Test result 5: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb06");
    printf("Test result 6: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb07");
    printf("Test result 7: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb08");
    printf("Test result 8: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb09");
    printf("Test result 9: %d\n", status);
    if (status != 0) { return -1; }
    
    status = testSortWeights("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb10");
    printf("Test result 10: %d\n", status);
    if (status != 0) { return -1; }
    
    return 0;
}
