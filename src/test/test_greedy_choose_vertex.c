#include "../../include/test/test_greedy_choose_vertex.h"

int testGreedyChooseVertex(const char* filepath)
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

    unsigned int chosenVertices[instance->numVertices];
    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	chosenVertices[i] = 0;
    }

    unsigned int numChosenVertices = 0;
    unsigned int vertex, color;
    SolutionValue solutionValue;
    solutionValue.bestValue = 0.0f;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);
    float alpha = 1.0f;
    
    for (i = 0; i < instance->numColors; i++)
    {
	solutionValue.colorValues[i] = 0.0f;
    }
    
    if (greedyChooseVertex(instance, sortedWeights, chosenVertices, numChosenVertices, &vertex, &color, &solutionValue, alpha) != 0)
    {
	return TST_ERR_GREEDY_CHOOSE_VERTEX;
    }

    printf("Vertex: %d\n", vertex);
    printf("Weight: %f\n", instance->weights[vertex]);
    printf("Color: %d\n", color);
    
    return 0;
}

int main()
{
    srand(time(NULL));
    testGreedyChooseVertex("/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb10");
    
    return 0;
}
