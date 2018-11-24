#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include <stdlib.h>

#define OUT_SUCCESS 0
#define ERR_MALLOC -1

// Defines a problem instance.
typedef struct instance_s
{
    unsigned int numColors;
    unsigned int numVertices;
    unsigned int** graph;
    float* weights;
    
} Instance;


// Constructor:
int newInstance(Instance** instance, unsigned int numColors, unsigned int numVertices);

// Destructor:
void destroyInstance(Instance* instance);

// Functions:
void addEdge(Instance* instance, unsigned int v, unsigned int u);
void setWeight(Instance* instance, unsigned int vertex, float weight);

int existsEdge(Instance* instance, unsigned int v, unsigned int u);

#endif // __INSTANCE_H__
