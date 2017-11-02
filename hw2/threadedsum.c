#include "threadedsum.h"
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void *subproblem(void *_args) {
    threadedsum_args *args = (threadedsum_args*)_args;
    int *p = args->arr;
    int *q = args->arr+1;
    int *end = p+args->num;
    args->sum = 0LL;
    for (;q<end;++p,++q) args->sum += *q - *p;
}

long long int threadedsum(int *array, size_t num, size_t thread_num) {
    long long int sum = 0LL;
    assert(num>0);
    if (thread_num>num) thread_num = num;
    int chunk_size = num/thread_num; // ceil
    pthread_t *threads = NULL;
    threads = (pthread_t*)malloc(sizeof(pthread_t)*thread_num);
    assert(threads!=NULL);
    threadedsum_args *thread_args = NULL;
    thread_args = (threadedsum_args*)malloc(sizeof(threadedsum_args)*thread_num);
    assert(thread_args!=NULL);
    int i=0;
    int pre = thread_num-1;
    for (i=0; i<pre; ++i) {
        thread_args[i].num = chunk_size;
        thread_args[i].arr = array+(chunk_size*i);
        assert(pthread_create(threads+i, NULL, subproblem, (void*)(thread_args+i))==0);
    }
    thread_args[pre].num = chunk_size+(num-chunk_size*thread_num);
    thread_args[pre].arr = array+(chunk_size*pre);
    assert(pthread_create(threads+pre, NULL, subproblem, (void*)(thread_args+pre))==0);
    for (i=0; i<thread_num; ++i) {
        pthread_join(threads[i], NULL);
        sum += thread_args[i].sum;
        if (i>0) sum += array[i*chunk_size]-array[i*chunk_size-1]; // interval
    }
    free(threads);
    free(thread_args);
    return sum;
}
