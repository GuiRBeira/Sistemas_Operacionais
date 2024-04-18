#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    key_t k = ftok("/sys", 'A');
    int shmid = shmget(k, 2048, 0666|IPC_CREAT);
    char *data = (char *)shmat(shmid,0,0);
    if((argc > 1) && !strcmp(argv[1],"apagar")){
        shmdt(data);
        shmctl(shmid, IPC_RMID,0);
    } else if(argc > 1){
        strncpy(data, argv[1], 2048);
    } else {
        printf("shm: %s\n", data);
    }
    return 0;
}