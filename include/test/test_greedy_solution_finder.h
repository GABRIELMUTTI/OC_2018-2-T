#ifndef __TEST_GREEDY_SOLUTION_FINDER_H_
#define __TEST_GREEDY_SOLUTION_FINDER_H_

#include "../instance.h"
#include "../solution.h"
#include "../instance_loader.h"
#include "../grasp.h"

#include <time.h>

#define TST_SUCCESS 0
#define TST_ERR_LOAD_INSTANCE -1
#define TST_ERR_GREEDY_CHOOSE_VERTEX -2
#define TST_ERR_SORT_WEIGHTS -3
#define TST_ERR_GREEDY_SOLUTION_FINDER -4




int testGreedySolutionFinder(const char* filepath);
int main();

#endif // __TEST_GREEDY_SOLUTION_FINDER_H_
