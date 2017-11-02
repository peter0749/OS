#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct shmid_ds shmd;
struct ipc_perm perm;
int shm_id;

int main(void) {
    int ret_status=0;
    shm_id = shmget(IPC_PRIVATE, 32, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL);
    if (shm_id<0) {
        perror("Error on shmget()");
        exit(1);
    }
    pid_t pid = fork();
    if (pid<0) {
        perror("Error on fork()");
        exit(2);
    }
    if (pid==0) { // child get information of shared memory segment
        if (shmctl(shm_id, IPC_STAT, &shmd)<0) {
            perror("Error on shmctl1");
            exit(3);
        }
        printf("Segment ID: %d\n", (int)shm_id);
#ifdef __APPLE__
        printf("Key: %d\n", (int)shmd.shm_perm._key);
#elif defined __linux__
        printf("Key: %d\n", (int)shmd.shm_perm.__key);
#else
        printf("Key: %d\n", (int)shmd.shm_perm.key);
#endif
        printf("Mode(in oct): %0o\n", (int)shmd.shm_perm.mode);
        printf("Owner UID: %d\n", (int)shmd.shm_perm.uid);
        printf("Size: %d\n", (int)shmd.shm_segsz);
        printf("Number of attaches: %d\n", (int)shmd.shm_nattch);
    } else { // parent deallocate shared memory
        wait(&ret_status); // wait child process to terminate
        if(ret_status!=0) exit(5); // child exited abnormally
        if (shmctl(shm_id, IPC_RMID, &shmd)<0) {
            perror("Error on shmctl2");
            exit(4);
        }
    }
    return 0; // process exit normally
}
