#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/instance_loader.h"
#include "../include/grasp.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char* argv[])
{
    int numIterations = atoi(argv[1]);
    float alpha = atof(argv[2]);
    const char* filepath = argv[3];

    Instance* instance = NULL;

    printf("Loading instance %s, with alpha %f, running for %d iterations.\n", filepath, alpha, numIterations);
    
    if (loadInstance(&instance, filepath) != 0) { return -1; }

    Solution* solution = NULL;
    SolutionValue value;
    value.colorValues = malloc(sizeof(float) * instance->numColors);

    srand(time(NULL));
    if (grasp(instance, &solution, &value, numIterations, alpha)) { return -2; }

    printf("Done!\n");
    return 0;
}
