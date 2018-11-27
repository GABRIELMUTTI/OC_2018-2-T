#ifndef __GRASP_H__
#define __GRASP_H__

#include "../include/instance.h"
#include "../include/solution.h"

#include <stddef.h>
#include <math.h>

typedef struct neighbour_s
{
    unsigned int inColor;
    unsigned int outColor;
    unsigned int vertex;
    
} Neighbour;

typedef struct vertexWeight_s
{
    unsigned int vertex;
    float weight;
    
} VertexWeight;


int grasp(Instance* instance, Solution** solution, SolutionValue* value, unsigned int numIterations, float alpha);
int greedySolutionFinder(Instance* instance, Solution** solution, SolutionValue* solutionValue, VertexWeight* sortedWeights, float alpha);
int bestImprovementLocalSearch(Instance* instance, Solution* currentSolution, SolutionValue* solutionValue);
int findNeighbours(Instance* instance, Solution* solution, Neighbour** neighbours, unsigned int* numNeighbours);
int greedyChooseVertex(Instance* instance, VertexWeight* sortedWeights, unsigned int* chosenVertices, unsigned int numChosenVertices, unsigned int* vertex, unsigned int* color, SolutionValue* value, float alpha);
int sortWeights(Instance* instance, VertexWeight** sortedWeights);



#endif // __GRASP_H__
