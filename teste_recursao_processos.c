#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t p = getpid();
    int num, fat = 1;
    printf("Digite o valor do fatorial: ");
    scanf("%d", &num);

    for(int i = 1; i <= num; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            // Erro ao criar o processo filho
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Processo filho
            fat *= i;
            printf("Processo filho %d calculou parte do fatorial: %d\n", getpid(), fat);
            return fat;
        }
    }

    // Processo pai espera pelos filhos
    for (int i = 0; i < num; i++) {
        int status;
        wait(&status);
        fat *= WEXITSTATUS(status);
    }

    printf("O fatorial de %d é: %d\n", num, fat);
    return 0;
}