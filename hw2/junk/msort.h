#ifndef __INCLUDE_MSORT_HEADER
#define __INCLUDE_MSORT_HEADER
#include <stddef.h>
#include <pthread.h>

typedef struct {
    char *array;
    char *ext;
    size_t block;
    int i;
    int m;
    int n;
    int (*cmp)(const void *a, const void *b);
} _TASK_ARGS;

typedef struct {
    pthread_t th;
    _TASK_ARGS args;
} _TASK_OBJ;

void merge(char *array, char *ext, size_t block, int i, int m, int n, int (*cmp)(const void *a, const void *b));
void mergeOnePass(char *array, char *ext, size_t block, int n, int s, int (*cmp)(const void *a, const void *b), size_t CPU_N, _TASK_OBJ *_th_pool, size_t min_nel);
void my_mergeSort(void *array, size_t n, size_t block, int (*cmp)(const void *a, const void *b), size_t min_nel);

#endif
