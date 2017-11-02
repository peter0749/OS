/*
 * A very simple implementation of parallel merge sort
 */
#ifndef __INCLUDE_MSORT_HEADER
#define __INCLUDE_MSORT_HEADER
//#define PARALLEL
#ifdef PARALLEL
#include <pthread.h>
#endif

#ifdef PARALLEL
typedef struct{
    char *array;
    size_t block;
    int L, R;
    int (*cmp)(const void *, const void *);
    int depth;
    int MAXDEPTH;
}MSORT_ARGS;
#endif

void merge(char *, size_t, int, int, int, int (*cmp)(const void *, const void *));
void devide(char *, size_t, int, int, int (*cmp)(const void *, const void *) ,int, int);
void *devide_thread(void*);
void mymergesort(void *, size_t , size_t , int, int (*cmp)(const void *, const void *));

#endif
