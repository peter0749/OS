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
    mem = (char*)malloc(40*MB);
    fprintf(stderr, "PID: %d\nPress ENTER to write 40 MB.\n", (int)pid);
    getchar();
    for (i=0; i<40*MB; ++i) mem[i]=rand();
    fprintf(stderr, "Press ENTER to exit\n");
    getchar();
    free(mem);
    mem = NULL;
    return 0;
}
