#ifndef __GREEDY_H__
#define __GREEDY_H__

#include "../include/instance.h"
#include "../include/solution.h"

#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

typedef struct vertexWeight_s
{
    unsigned int vertex;
    float weight;
    
} VertexWeight;


int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue, uint* sortedVertices, float alpha);
void greedyChooseVertex(Instance* instance, Solution* solution, uint* sortedVertices, uint* chosenVertices, uint numChosenVertices, uint* vertex, uint* color, uint* conflict, float alpha);
void constructRcl(Instance* instance, Solution* solution, uint* sortedVertices, uint* chosenVertices, uint* rclVertex, uint* rclColor, uint* rclConflict, uint rclSize);



#endif // __GREEDY_H__
