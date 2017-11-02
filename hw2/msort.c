/*
 * A very simple implementation of parallel merge sort
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "msort.h"

void merge(char *array, size_t block, int L, int M, int R, int (*cmp)(const void *a, const void *b)){
    int i, j, k, t;
    char *temp = (char*)malloc(block*(R-L+1));
    i=L; j=M+1; k=0;
    while(i<=M && j<=R){
        t = cmp(array+block*i, array+block*j);
        if(t<0){
            memcpy(temp+k*block, array+block*i, block);
            ++i;
        }else{
            memcpy(temp+k*block, array+block*j, block);
            ++j;
        }
        ++k;
    }
    while(i<=M) memcpy(temp+(k++)*block, array+block*(i++), block);
    while(j<=R) memcpy(temp+(k++)*block, array+block*(j++), block);
    memcpy(array+block*L, temp, block*(R-L+1));
    free(temp);
    //pass
}
void devide(char *array , size_t block, int L, int R, int (*cmp)(const void *a, const void *b) ,int depth, int MAXDEPTH){
    //pass
    if(L==R)return;
    int M=(L+R)>>1;
#ifdef PARALLEL
    if(depth < MAXDEPTH){
        MSORT_ARGS *arg1 = NULL;
        arg1 = (MSORT_ARGS*)malloc(sizeof(MSORT_ARGS));
        assert(arg1!=NULL);
        MSORT_ARGS *arg2 = NULL;
        arg2 = (MSORT_ARGS*)malloc(sizeof(MSORT_ARGS));
        assert(arg2!=NULL);
        arg1->array = array;
        arg1->block = block;
        arg1->L = L;
        arg1->R = M;
        arg1->cmp = cmp;
        arg1->depth = depth+1;
        arg1->MAXDEPTH = MAXDEPTH;
        arg2->array = array;
        arg2->block = block;
        arg2->L = M+1;
        arg2->R = R;
        arg2->cmp = cmp;
        arg2->depth = depth+1;
        arg2->MAXDEPTH = MAXDEPTH;
        pthread_t *thread1=NULL, *thread2=NULL;
        thread1 = (pthread_t*)malloc(sizeof(thread1));
        assert(thread1!=NULL);
        thread2 = (pthread_t*)malloc(sizeof(thread1));
        assert(thread2!=NULL);
        if(pthread_create(thread1, NULL, devide_thread, (void*)(arg1))) exit(-1);
        if(pthread_create(thread2, NULL, devide_thread, (void*)(arg2))) exit(-1);
        pthread_join(*thread1, NULL);
        pthread_join(*thread2, NULL);
        free(arg1), free(arg2);
        free(thread1), free(thread2);
    }else{
        devide(array, block, L,M,cmp, depth+1, MAXDEPTH);
        devide(array, block, M+1, R,cmp, depth+1, MAXDEPTH);
    }
#else
    devide(array, block, L,M,cmp, depth+1, MAXDEPTH);
    devide(array, block, M+1, R,cmp, depth+1, MAXDEPTH);
#endif
    merge(array, block, L, M, R, cmp);
}
#ifdef PARALLEL
void *devide_thread(void *init){
    MSORT_ARGS *s = (MSORT_ARGS*)init;
    devide(s->array,s->block,s->L,s->R,s->cmp,s->depth, s->MAXDEPTH);
    pthread_exit(NULL);
}
#endif

void mymergesort(void *array, size_t num, size_t block, int MAXDEPTH, int (*cmp)(const void *a, const void *b)){
    devide((char*)array, block, 0, num-1, cmp, 0, MAXDEPTH);
}
