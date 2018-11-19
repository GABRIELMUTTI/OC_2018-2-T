#include <stdlib.h>

#define OUT_SUCCESS 0
#define ERR_MALLOC -1

// Defines a problem instance.
typedef struct instance_s
{
    unsigned int numColors;
    unsigned int numVertices;
    unsigned int** graph;
    unsigned int* weights;
    
} Instance;

int newInstance(Instance* instance, unsigned int numColors, unsigned int numVertices, unsigned int* weights);
void destroyInstance(Instance* instance);
void addEdge(Instance* instance, unsigned int v, unsigned int u);
int existsEdge(Instance* instance, unsigned int v, unsigned int u);
