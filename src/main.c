#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/instance_loader.h"
#include "../include/grasp.h"
#include "../include/solution_saver.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int numIterations = atoi(argv[1]);
    float alpha = atof(argv[2]);
    const char* instanceFilepath = argv[3];
    const char* saveFilepath = argv[4];

    Instance* instance = NULL;

    printf("Loading instance %s, with alpha %f, running for %d iterations.\n", instanceFilepath, alpha, numIterations);
    
    if (loadInstance(&instance, instanceFilepath) != 0) { return -1; }

    Solution* solution = NULL;
    SolutionValue value;
    value.colorValues = malloc(sizeof(float) * instance->numColors);

    srand(time(NULL));
    if (grasp(instance, &solution, &value, numIterations, alpha)) { return -2; }

    /*
    unsigned int i, j;
    for (i = 0; i < instance->numVertices; i++)
    {
	unsigned int vertexColor = solution->coloration[i];
	unsigned int numConflictsBefore = countConflicts(instance, solution, i);
	
	for (j = 0; j < instance->numColors; j++)
	{
	    if (j != vertexColor)
	    {
		solution->coloration[i] = j;
		unsigned int numConflicts = countConflicts(instance, solution, i);

		if (numConflicts < numConflictsBefore)
		{
		    printf("can do better.\n");
		}
	    }
	}

	solution->coloration[i] = vertexColor;
    }
    */
    
    printf("Done!\n");
    printf("Saving...\n");

    printf("Final Checkage: %f <%d, %d>\n", value.bestValue, solution->isFactible, countSolutionConflicts(instance, solution));
    
    unsigned int conflicts = countSolutionConflicts(instance, solution);
    
    saveSolution(instance, solution, conflicts, value, saveFilepath, instanceFilepath, alpha, numIterations);
    
    return 0;
}
