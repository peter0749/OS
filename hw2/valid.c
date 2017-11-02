#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int cmp(const void *a, const void *b) {
    if (*(int*)a < *(int*)b) return -1;
    if (*(int*)a > *(int*)b) return 1;
    return 0;
}

long long int sum(int *array, int num) {
    long long int s = 0;
    int *p = array;
    int *q = array+1;
    int *end = array+num;
    for (;q<end;++p, ++q) s += *q - *p;
    return s;
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
    qsort(array, array_size, sizeof(array[0]), cmp);
    printf("%lld\n", sum(array, array_size));
    return 0;
}
