/*
 * A very simple implementation of parallel merge sort
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
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
    if (i<=M) memcpy(temp+k*block, array+block*i, block*(M-i+1));
    if (j<=R) memcpy(temp+k*block, array+block*j, block*(R-j+1));
    memcpy(array+block*L, temp, block*(R-L+1));
    free(temp);
    //pass
}
void devide(char *array , size_t block, int L, int R, int (*cmp)(const void *a, const void *b) ,int depth, int MAXDEPTH){
    //pass
    if(L==R)return;
    int M=(L+R)>>1;
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
        int re1=0, re2=0;
        if(re1=(pthread_create(thread1, NULL, devide_thread, (void*)(arg1)))) {
            qsort(array+L*block, M-L+1, block, cmp);
        }
        if(re2=(pthread_create(thread2, NULL, devide_thread, (void*)(arg2)))) {
            qsort(array+(M+1)*block, R-M, block, cmp);
        }
        if (!re1)
            pthread_join(*thread1, NULL);
        if (!re2)
            pthread_join(*thread2, NULL);
        free(arg1), free(arg2);
        free(thread1), free(thread2);
        merge(array, block, L, M, R, cmp);
    }else{
        qsort(array+L*block, R-L+1, block, cmp);
        return;
    }
    merge(array, block, L, M, R, cmp);
}
void *devide_thread(void *init){
    MSORT_ARGS *s = (MSORT_ARGS*)init;
    devide(s->array,s->block,s->L,s->R,s->cmp,s->depth, s->MAXDEPTH);
}

void mymergesort(void *array, size_t num, size_t block, int MAXCORE, int (*cmp)(const void *a, const void *b)){
    int MAXDEPTH = ceil(log2(MAXCORE));
    devide((char*)array, block, 0, num-1, cmp, 0, MAXDEPTH);
}
