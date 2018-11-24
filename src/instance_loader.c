#include "../include/instance_loader.h"

int loadInstance(Instance** instancePtr, const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    const char* delimiter = " \n";
    
    char* line;

    if (file == 0) { return -1; }
    if (getLine(file, &line, delimiter) != 0) { return ERR_GETLINE; }

    char* strNumVertices = strtok(line, delimiter);
    unsigned int numVertices = atoi(strNumVertices);
    
    char* strNumEdges = strtok(NULL, delimiter);
    int numEdges = atoi(strNumEdges);

    char* strNumColors = strtok(NULL, delimiter);
    unsigned int numColors = atoi(strNumColors);
    free(line);

    if (newInstance(instancePtr, numColors, numVertices) != 0) { return ERR_NEW_INSTANCE; }
    Instance* instance = *instancePtr;
    
    if (getLine(file, &line, delimiter) != 0) { return ERR_GETLINE; }
    
    instance->weights[0] = strtof(strtok(line, delimiter), NULL);
    
    unsigned int i;
    for (i = 1; i < instance->numVertices; i++)
    {
	instance->weights[i] = strtof(strtok(NULL, delimiter), NULL);
    }
    
    free(line);

    unsigned int v, u;
    for (i = 0; i < numEdges; i++)
    {
	if (getLine(file, &line, delimiter) != 0) { return ERR_GETLINE; }
	v = atoi(strtok(line, delimiter));
	u = atoi(strtok(NULL, delimiter));

	instance->graph[v][u] = 1;
	instance->graph[u][v] = 1;
	
	free(line);
    }
    
    return 0;
}

int getLine(FILE* file, char** line, const char* delimiters)
{
    size_t lineSize = 0;
    if (getline(line, &lineSize, file) < 0)
    {
	free(*line);
	return -1;
    }
    
    return 0;
}

