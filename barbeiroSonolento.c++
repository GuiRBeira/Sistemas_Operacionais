#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "threads.h"
#include "semaphore.h"
#include <unistd.h>

#define NUM_CADEIRAS 5
#define VERMELHO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define RESET   "\x1b[0m"

Semaphore semaforo;
int clientes_esperando;

Mutex mutex;

int barbeiro(int id) {
    while(1) {
        if (clientes_esperando == 0) {
            printf("O barbeiro está dormindo...\n");
	        mutex.WBarbeiro();
        } else {
            mutex.CCliente();
            printf("O barbeiro está cortando o cabelo de um cliente. Clientes esperando: %d\n", clientes_esperando);     
            //cortando o cabelo
            //mutex.lock();
            semaforo.p();
            clientes_esperando--;
            semaforo.v();
            //mutex.unlock();
            sleep(3);      
        }
    }
    printf(VERDE "\n%d\n", id);
    return 0;
}

int cliente(int id) {
    if (clientes_esperando < NUM_CADEIRAS) {
    	printf("Cliente %d entrou na barbearia. Clientes esperando: %d\n", id, clientes_esperando);
        //mutex.lock();
        semaforo.p();
        clientes_esperando++;
        semaforo.v();
        //mutex.unlock();
	    mutex.CBarbeiro();
        mutex.WCliente(id);
        printf(VERDE "Cliente %d cortando o cabelo." RESET "\n", id);      
    } else {
        printf(VERMELHO "A barbearia está cheia. Cliente %d foi embora." RESET "\n", id);
        return -10;
    }
    return id;
}

int main() {
    Thread *clientes[NUM_CLIENTES];
    Thread *barb;

    mutex.init();
    clientes_esperando = 0;
    int status;
    // Inicializa o barbeiro
    barb = new Thread(&barbeiro,0);
    // Inicializa os clientes
    for (int i = 0; i < NUM_CLIENTES; i++) {
        clientes[i] = new Thread(&cliente, i);
        sleep(1); // Simula chegada de clientes em intervalos
    }
    // Aguarda o término das threads    
    for (int j = 0; j < NUM_CLIENTES; j++) {
        clientes[j]->join(&status);               
    }
    barb->join(NULL);	
    return 0;
}