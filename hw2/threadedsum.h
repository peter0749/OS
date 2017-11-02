#ifndef __INCLUDE_THREADED_SUM_HEADER
#define __INCLUDE_THREADED_SUM_HEADER
#include <stdlib.h>
typedef struct {
    size_t num;
    int *arr;
    long long int sum;
} threadedsum_args;

void *subproblem(void *_args);
long long int threadedsum(int *array, size_t num, size_t thread_num);
#endif
