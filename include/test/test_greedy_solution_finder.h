#ifndef __TEST_GREEDY_SOLUTION_FINDER_H_
#define __TEST_GREEDY_SOLUTION_FINDER_H_

#include "../instance.h"
#include "../solution.h"
#include "../instance_loader.h"
#include "../grasp.h"

#include <time.h>
#include <math.h>

#define TST_SUCCESS 0
#define TST_ERR_LOAD_INSTANCE -1
#define TST_ERR_GREEDY_CHOOSE_VERTEX -2
#define TST_ERR_GREEDY_SOLUTION_FINDER -3
#define TST_ERR_WRONG_COLOR_VALUES -4

int testGreedySolutionFinder(const char* filepath);
void tryToImprove(Instance* instance, Solution* solution);
void printNeighbourColors(Instance* instance, Solution* solution, unsigned int vertex);
#endif // __TEST_GREEDY_SOLUTION_FINDER_H_
