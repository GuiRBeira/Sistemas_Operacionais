#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <mensagem> ou %s apagar\n", argv[0], argv[0]);
        //return 1;
    }
    
    key_t k = ftok("/sys", 'A');
    if (k == -1) {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(k, 2048, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    char *data = (char *)shmat(shmid, 0, 0);
    if (data == (void *)-1) {
        perror("shmat");
        return 1;
    }

    if (!strcmp(argv[1], "apagar")) {
        if (shmdt(data) == -1) {
            perror("shmdt");
            return 1;
        }
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("shmctl");
            return 1;
        }
        printf("Memória compartilhada removida com sucesso.\n");
    } else {
        if(argv[1] != NULL){
            strncpy(data, argv[1], 2048);    
        }
        printf("Dados escritos na memória compartilhada.\n");
        printf("data : %s", data);
    }

    return 0;
}
