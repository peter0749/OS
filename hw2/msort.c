/*
 * A very simple implementation of parallel merge sort
 */
#include <stdlib.h>
#include <string.h>
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
        MSORT_ARGS arg1 = 
        {
            array, block, L, M, cmp, depth+1
        };
        MSORT_ARGS arg2 = 
        {
            array, block, M+1, R, cmp, depth+1
        };
        pthread_t thread1, thread2;
        if(pthread_create(&thread1, NULL, devide_thread, (void*)(&arg1))) exit(-1);
        if(pthread_create(&thread2, NULL, devide_thread, (void*)(&arg2))) exit(-1);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
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
