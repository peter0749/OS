#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MB 1024*1024

int main(void) {
    srand(time(NULL));
    pid_t pid = getpid();
    int i=0;
    char *mem = NULL;
    fprintf(stderr, "PID: %d\n", (int)pid);
    mem = (char*)malloc(40*MB);
    getchar();
    for (i=0; i<40*MB; ++i) mem[i]=rand();
    getchar();
    free(mem);
    mem = NULL;
    return 0;
}
