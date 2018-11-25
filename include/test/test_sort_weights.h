#ifndef __TEST_SORT_WEIGHTS_H__
#define __TEST_SORT_WEIGHTS_H__

#include "../instance.h"
#include "../instance_loader.h"
#include "../grasp.h"

#define TST_SUCCESS 0
#define TST_ERR_LOAD_INSTANCE -1
#define TST_ERR_SORT_WEIGHTS -2
#define TST_ERR_NOT_SORTED -3
#define TST_ERR_WRONG_VERTEX_WEIGHT -4
#define TST_ERR_MISSING_WEIGHTS -5

int testSortWeights(const char* filepath);
int test_main();


#endif // __TEST_SORT_WEIGHTS_H__
