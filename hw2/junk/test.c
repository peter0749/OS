#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "msort.h"
#ifndef MAXN
#define MAXN 1000000
#endif

int cmp(const void *a, const void *b) {
    if (*((int*)a) < *((int*)b)) return -1;
    if (*((int*)a) > *((int*)b)) return 1;
    return 0;
}

int main(void) {
    int array[MAXN];
    for (int i=0; i<MAXN; ++i) array[i]=rand();
#ifdef QSORT
    qsort(array,MAXN, sizeof(int), cmp);
#else
    my_mergeSort(array,MAXN,sizeof(int),cmp, 2048);
#endif
    for (int i=0; i<MAXN; ++i) printf("%d\n", array[i]);
    return 0;
}
