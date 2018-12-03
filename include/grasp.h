#ifndef __GRASP_H__
#define __GRASP_H__

#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/greedy.h"
#include "../include/local_search.h"
#include "../include/path_relinking.h"

#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef unsigned int uint;

int grasp(Instance* instance, Solution** solution, SolutionValue* value, uint numIterations, float alpha);
int sortVerticesByDegree(Instance* instance, unsigned int** sortedVertices);

#endif // __GRASP_H__
