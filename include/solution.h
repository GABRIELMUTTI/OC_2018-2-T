#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "instance.h"

#include <stdlib.h>

#define OUT_SUCCESS 0
#define ERR_MALLOC -1

// Defines a solution to a instance;
typedef struct solution_s
{
    unsigned int* coloration;
    unsigned int* numVertexPerColor;
    int isFactible;
    
} Solution;

typedef struct solutionValue_s
{
    float* colorValues;
    float bestValue;
} SolutionValue;

// Construtor:
int newSolution(Solution** solution, Instance* instance);

// Destructor:
void destroySolution(Solution* solution);

// Functions:
int checkFactibility(Instance* instance, Solution* solution);
int checkVertexFactibility(Instance* instance, Solution* solution, unsigned int vertex);
void colorVertex(Solution* solution, unsigned int vertex, unsigned int color);
SolutionValue getValue(Instance* instance, Solution* solution);

#endif // __SOLUTION_H__




