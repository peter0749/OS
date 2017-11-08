#include "msort.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>

void merge(char *array, char *ext, size_t block, int i, int m, int n, int (*cmp)(const void *a, const void *b)){
    int j, k, t;
    j=m+1;
    k=i;

    while (i<=m && j<=n) {
        if (cmp(array+i*block, array+j*block)<=0)
            memcpy(ext+(k++)*block, array+(i++)*block, block);
        else
            memcpy(ext+(k++)*block, array+(j++)*block, block);
    }
    if (i>m) // remainding elements
        memcpy(ext+k*block, array+j*block, block*(n-j+1));
    else 
        memcpy(ext+k*block, array+i*block, block*(m-i+1));
}

void *mergeWrapper(void *__args) {
    _TASK_ARGS *args = (_TASK_ARGS*)__args;
    merge(args->array, args->ext, args->block, args->i, args->m, args->n, args->cmp);
    pthread_exit(NULL);
}

void mergeOnePass(char *array, char *ext, size_t block, int n, int s, int (*cmp)(const void *a, const void *b), size_t th_num, _TASK_OBJ *pthread_obj, size_t minimum_nel) {
    /* Implement parallelization here:
    */
    int i,j;
    int front=0, rear=0, max_size=th_num; // fifo method
    if (s<minimum_nel) {
        for (i=1; i <= n-2*s+1; i+=(s<<1)) 
            merge(array, ext, block, i, i+s-1, i+2*s-1, cmp);
    } else {
        for (i=1; i <= n-2*s+1; i+=(s<<1)) {
            if ((rear+1)%max_size==front) { // full, pop 1
                pthread_join(pthread_obj[front].th, NULL); // wait a job to done.
                front = (front+1)%max_size;
            }
            pthread_obj[rear].args.array=array;
            pthread_obj[rear].args.ext=ext;
            pthread_obj[rear].args.block=block;
            pthread_obj[rear].args.i=i;
            pthread_obj[rear].args.m=i+s-1;
            pthread_obj[rear].args.n=i+2*s-1;
            pthread_obj[rear].args.cmp=cmp;
            pthread_create(&pthread_obj[rear].th, NULL, mergeWrapper, &pthread_obj[rear].args);
            rear = (rear+1)%max_size; // push 1
            // merge(array, ext, block, i, i+s-1, i+2*s-1, cmp);
        }
    }
    if (i+s-1<n)
        merge(array, ext, block, i, i+s-1, n, cmp);
    else 
        memcpy(ext+i*block, array+i*block, block*(n-i+1));
    while (front!=rear) {
        pthread_join(pthread_obj[front].th, NULL);
        front = (front+1)%max_size;
    }
}

void my_mergeSort(void *a, size_t n, size_t block, int (*cmp)(const void *a, const void *b), size_t minimum_nel) {
    int s=1;
    /*
     * Data Structure in C: p.348 
     * :"sort a[1:n] using the merge sort method"
     * We need to convert it into 0-based.
     */
    char *array = (char*)(a-block);
    char *ext = NULL; ext=(char*)malloc(block*(n+1));
    assert(ext!=NULL);
    long CPU_NUM = sysconf(_SC_NPROCESSORS_ONLN);
    _TASK_OBJ *th_pool = NULL;
    th_pool = (_TASK_OBJ*)malloc(sizeof(_TASK_OBJ)*(CPU_NUM));
    while (s<n) {
        mergeOnePass(array, ext, block, n, s, cmp, CPU_NUM, th_pool, minimum_nel);
        s<<=1;
        mergeOnePass(ext, array, block, n, s, cmp, CPU_NUM, th_pool, minimum_nel);
        s<<=1;
    }
    free(th_pool);
    free(ext);
}

