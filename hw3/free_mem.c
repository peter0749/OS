#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define GB (1<<30)

int main(int argc, char **argv) {
    srand(time(NULL));
    struct timeval sv, endv;
    struct timezone sz, endz;
    pid_t pid = getpid();
    int i=0, j=0;
    int num = atoi(argv[1]);
    char **mem = NULL;
    fprintf(stderr, "PID: %d\nPress ENTER to start.", (int)pid);
    getchar();
    gettimeofday(&sv, &sz);
    mem = (char**)malloc(sizeof(char**)*num);
    for (i=0; i<num; ++i) mem[i] = (char*)malloc(GB);
    for (i=0; i<num; ++i) {
        for (j=0; j<GB; ++j) mem[i][j] = rand();
        fprintf(stderr, "Allocated %d GB of memory!\n", i+1);
    }
    gettimeofday(&endv, &endz);
    float elapsed = (endv.tv_sec-sv.tv_sec)+(endv.tv_usec-sv.tv_usec)*1e-6;
    fprintf(stderr, "Allocated %d GB of memory in %.2f seconds.\nPress ENTER to release memory.\n", num, elapsed);
    getchar();
    for (i=0; i<num; ++i) free(mem[i]);
    free(mem);
    fprintf(stderr, "Released %d GB of memory.\nProgram exit normally.\n", num);
    mem = NULL;
    return 0;
}
