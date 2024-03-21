/*Pesquise na documentação do POSIX (ou api equivalente no windows), 
e crie uma função para sua biblioteca para disparar uma mensagem a cada x segundos de acordo com a assinatura a seguir:
printsinc(char* msg, int segundos);
Se o usuário apertar a tecla CTRL Z três vezes o programa deverá ser encerrado.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void printf_per_second(char* msg, int sec){
    while(1){
        alarm(sec);
        pause();
        write(1, msg, strlen(msg));
    }    
}

void sair(){
    static int ctrl_z_count = 0;
    ctrl_z_count++;
    if(ctrl_z_count >= 3){
        write(1, "\nEncerrando\n", 13);
        exit(0);
    }
}

int main(){
    char *msg = (char *)calloc(20, sizeof(char));
    printf("Digite a mensagem a ser exibida: ");
    fgets(msg, 20, stdin);
    signal(SIGTSTP, sair);
    printf_per_second(msg, 1);
    free(msg);
    return 0;
}

