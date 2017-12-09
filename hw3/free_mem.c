#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define GB (1<<30)

int main(int argc, char **argv) {
    srand(time(NULL));
    pid_t pid = getpid();
    int i=0, j=0;
    int num = atoi(argv[1]);
    char **mem = NULL;
    fprintf(stderr, "PID: %d\n", (int)pid);
    mem = (char**)malloc(sizeof(char**)*num);
    for (i=0; i<num; ++i) mem[i] = (char*)malloc(GB);
    for (i=0; i<num; ++i) for (j=0; j<GB; ++j) mem[i][j] = rand();
    for (i=0; i<num; ++i) free(mem[i]);
    free(mem);
    mem = NULL;
    return 0;
}
