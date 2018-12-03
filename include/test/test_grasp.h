#ifndef __TEST_GRASP_H__
#define __TEST_GRASP_H__

#include "../instance.h"
#include "../solution.h"
#include "../instance_loader.h"
#include "../grasp.h"

#include <time.h>
#include <math.h>

#define TST_SUCCESS 0
#define TST_ERR_LOAD_INSTANCE -1
#define TST_ERR_SORT_WEIGHTS -2
#define TST_ERR_GREEDY_SOLUTION_FINDER -3
#define TST_ERR_BEST_IMPROVEMENT_LOCAL_SEARCH -4
#define TST_ERR_GRASP -5
#define TST_ERR_WRONG_COLOR_VALUES -6
#define TST_ERR_WRONG_BEST_VALUE -7


int testGrasp(const char* filepath);

#endif // __TEST_GRASP_H__

