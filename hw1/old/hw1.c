#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

struct shmid_ds shmd;
struct ipc_perm perm;
int segment_id;

int main(int argc, char **argv) {
    int i, ret;
    if (argc<2) {
        fprintf(stderr, "Please pass Shared Memory ID as an argument!\n");
        fprintf(stderr, "Usage: ./hw1 YOUR_SHM_ID\n");
        fprintf(stderr, "YOUR_SHM_ID can be obtained by exectuing ./server\n");
        exit(-1);
    }
    segment_id = atoi(argv[1]);
    ret = shmctl(segment_id, IPC_STAT, &shmd);
    if (ret<0) {
        perror("Error on shmctl1");
        exit(-2);
    }
    printf("Segment ID: %d\n", (int)segment_id);
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
#ifdef __REMOVE_SHM
    ret = shmctl(segment_id, IPC_RMID, &shmd);
    if (ret<0) {
        perror("Error on shmctl2");
        exit(-2);
    }
#endif
    return 0;
}
