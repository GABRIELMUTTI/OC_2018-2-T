#include "../../include/test/test_greedy_choose_vertex.h"

int testGreedyChooseVertex(const char* filepath)
{
    Instance* instance = NULL;
    Solution* solution = NULL;
    newSolution(&solution, instance);

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }
    
    unsigned int chosenVertices[instance->numVertices];
    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	chosenVertices[i] = 0;
    }

    unsigned int numChosenVertices = 0;
    unsigned int vertex, color, conflict;
    SolutionValue solutionValue;
    solutionValue.bestValue = 0.0f;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);
    float alpha = 1.0f;
    
    for (i = 0; i < instance->numColors; i++)
    {
	solutionValue.colorValues[i] = 0.0f;
    }
    
    greedyChooseVertex(instance, solution, chosenVertices, numChosenVertices, &vertex, &color, &conflict, alpha);

    printf("Vertex: %d\n", vertex);
    printf("Weight: %f\n", instance->weights[vertex]);
    printf("Color: %d\n", color);
    
    return 0;
}
