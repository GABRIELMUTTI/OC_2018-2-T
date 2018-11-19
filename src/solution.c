#include "solution.h"

int newSolution(Solution* solution, Instance* instance)
{
    solution = malloc(sizeof(Solution));
    if (solution == 0) { return ERR_MALLOC; }
    
    solution->coloration = malloc(sizeof(unsigned int*) * instance->numColors);
    if (solution->coloration == 0) { return ERR_MALLOC; }
    
    unsigned int colorIndex;
    unsigned int i;
    for (colorIndex = 0; colorIndex < instance->numVertices; colorIndex++)
    {
	solution->coloration[colorIndex] = malloc(sizeof(unsigned int) * instance->numVertices);
	if (solution->coloration[colorIndex] == 0) { return ERR_MALLOC; }
	
	for (i = 0; i < instance->numVertices; i++)
	{
	    solution->coloration[colorIndex][i] = 0;
	}	
    }

    return OUT_SUCCESS;
}
