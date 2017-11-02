#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "msort.h"
#include "threadedsum.h"

int cmp(const void *a, const void *b) {
    if (*(int*)a < *(int*)b) return -1;
    if (*(int*)a > *(int*)b) return 1;
    return 0;
}

int main(int argc, char **argv) {
    if (argc<3) {
        fprintf(stderr, "Usage: ./hw2 seed array_size\n");
        exit(1);
    }
    int seed = atoi(argv[1]), i=0;
    srand(seed);
    size_t array_size = atoi(argv[2]);
    int *array = (int*)malloc(sizeof(int)*array_size);
    for (i=0; i<array_size; ++i) array[i] = rand();
    mymergesort(array, array_size, sizeof(array[0]), 1, cmp);
    printf("%lld\n", threadedsum(array, array_size, 4));
    return 0;
}
