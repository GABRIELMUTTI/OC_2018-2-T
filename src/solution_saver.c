#include "../include/solution_saver.h"

int saveSolution(Instance* instance, Solution* solution, unsigned int conflicts, SolutionValue solutionValue, const char* filepath, const char* instanceFilepath, float alpha, unsigned int numIterations)
{
    time_t currentTime;
    time(&currentTime);

    char* factibleFolderStr = "factible/";
    
    const char* filename = ctime(&currentTime);

    char fullFilepath[strlen(filename) + strlen(filepath) + strlen(factibleFolderStr)];
    memcpy(fullFilepath, filepath, strlen(filepath));
    
    
    if (solution->isFactible)
    {
	memcpy(fullFilepath + strlen(filepath), factibleFolderStr, strlen(factibleFolderStr));
	memcpy(fullFilepath + strlen(filepath) + strlen(factibleFolderStr), filename, strlen(filename) - 1);
	fullFilepath[strlen(filepath) + strlen(filename) + strlen(factibleFolderStr) - 1] = '\0';

	printf("fullpath: %s\n", fullFilepath);
    }
    else
    {
	memcpy(fullFilepath + strlen(filepath), filename, strlen(filename) - 1);
	fullFilepath[strlen(filepath) + strlen(filename) - 1] = '\0';
    }
    
    FILE* file = fopen(fullFilepath, "w");

    fprintf(file, "Instance: %s\n", instanceFilepath);
    fprintf(file, "Vertices: %d\n", instance->numVertices);
    fprintf(file, "Colors: %d\n", instance->numColors);
    fprintf(file, "NumIterations: %d\n", numIterations);
    fprintf(file, "Alpha: %f\n", alpha);

    char* strTrue = "true";
    char* strFalse = "false";
    char* factibleStr;
    if (solution->isFactible)
    {
	factibleStr = strTrue;
    }
    else
    {
	factibleStr = strFalse;
    }
    
    
    fprintf(file, "Is Factible?: %s\n", factibleStr);
    fprintf(file, "Conflicts: %d\n", conflicts);
    fprintf(file, "Solution Value: %f\n", solutionValue.bestValue);
    fprintf(file, "Vertex,\tColor\n");
    
    unsigned int i;
    for (i = 0; i < instance->numVertices; i++)
    {
	fprintf(file, "%d,\t%d\n", i, solution->coloration[i]);
    }

    fclose(file);

    return 0;
}
