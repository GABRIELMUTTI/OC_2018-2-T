#include "../../include/test/test_grasp.h"

int testGrasp(const char* filepath)
{

    const float EPSILON = 1e-4;
    Instance* instance = NULL;

    time_t seed = 1;
    srand(time(&seed));

    if (loadInstance(&instance, filepath) != 0)
    {
	return TST_ERR_LOAD_INSTANCE;
    }

    Solution* solution = NULL;
    SolutionValue solutionValue;
    solutionValue.colorValues = malloc(sizeof(float) * instance->numColors);

    float alpha = 0.02f;
    unsigned int numIterations = 5000;
    if (grasp(instance, &solution, &solutionValue, numIterations, alpha) != 0)
    {
	return TST_ERR_GRASP;
    }
    
    // Checks if the color values are valid.
    float colorValues[instance->numColors];
    unsigned int i;
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

    printf("Solution Value: %f\n", solutionValue.bestValue);

    for (i = 0; i < instance->numColors; i++)
    {
	printf("Color %d value: %f\n", i, solutionValue.colorValues[i]);
    }
    
    return TST_SUCCESS;
}
