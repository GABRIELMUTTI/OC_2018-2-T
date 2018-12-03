#ifndef __SOLUTION_SAVER_H__
#define __SOLUTION_SAVER_H__

#include "instance.h"
#include "solution.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

int saveSolution(Instance* instance, Solution* solution, unsigned int conflicts, SolutionValue solutionValue, const char* filepath, const char* instanceFilepath, float alpha, unsigned int numIterations);



#endif // __SOLUTION_SAVER_H__
