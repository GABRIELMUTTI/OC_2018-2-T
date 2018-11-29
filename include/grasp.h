#ifndef __GRASP_H__
#define __GRASP_H__

#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/greedy.h"
#include "../include/local_search.h"

#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

int grasp(Instance* instance, Solution** solution, SolutionValue* value, uint numIterations, float alpha);


#endif // __GRASP_H__
