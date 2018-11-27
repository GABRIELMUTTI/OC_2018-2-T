#ifndef __TEST_FIND_NEIGHBOURS_H__
#define __TEST_FIND_NEIGHBOURS_H__

#include "../instance.h"
#include "../solution.h"
#include "../instance_loader.h"
#include "../grasp.h"

#include <time.h>
#include <math.h>

#define TST_SUCCESS 0
#define TST_ERR_LOAD_INSTANCE -1
#define TST_ERR_GREEDY_CHOOSE_VERTEX -2
#define TST_ERR_SORT_WEIGHTS -3
#define TST_ERR_GREEDY_SOLUTION_FINDER -4
#define TST_ERR_FIND_NEIGHBOURS -5

int testFindNeighbours(const char* filepath);

#endif // __TEST_FIND_NEIGHBOURS_H__
