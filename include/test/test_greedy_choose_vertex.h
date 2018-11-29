#ifndef __TEST_GREEDY_CHOOSE_VERTEX_H__
#define __TEST_GREEDY_CHOOSE_VERTEX_H__

#include "../instance.h"
#include "../solution.h"
#include "../instance_loader.h"
#include "../grasp.h"

#include <time.h>

#define TST_SUCCESS 0
#define TST_ERR_LOAD_INSTANCE -1
#define TST_ERR_SORT_WEIGHTS -2
#define TST_ERR_GREEDY_CHOOSE_VERTEX -3


int testGreedyChooseVertex(const char* filepath);

#endif // __TEST_GREEDY_CHOOSE_VERTEX_H__
