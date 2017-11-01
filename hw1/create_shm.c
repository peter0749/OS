#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    key_t key = 0x0715; // try it first
    int shm_id = -1;
    shm_id = shmget(key,32,S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL);
    if (shm_id < 0) {
        key = IPC_PRIVATE;
        shm_id = shmget(key,32,S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL);
        if (shm_id < 0) {
            perror("Error on shmget");
            exit(-1);
        }
    }
    printf("Key: %d\n",(int)key);
    printf("Shared memory ID: %d\n", shm_id);
    printf("Created shared memory successfully.\nUse `ipcs -m` to identify it.\n");
    return 0;
}
