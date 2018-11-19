#include <stdlib.h>

// Defines a problem instance.
typedef struct instance_s
{
    unsigned int numColors;
    unsigned int numVertices;
    unsigned int** graph;
    unsigned int* weights;
    
} Instance;

// Defines a solution to a instance;
typedef struct solution_s
{
    unsigned int** coloration;
    unsigned int* sizeColors;
    
} Solution;

Instance* newInstance(unsigned int numColors, unsigned int numVertices, unsigned int** graph, unsigned int* weights);
void destroyInstance(Instance* instance);
int checkFactibility(Instance* instance, Solution* solution);
int existsEdge(Instance* instance, unsigned int v, unsigned int u);
