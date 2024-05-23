#ifndef __mutex_h
#define __mutex_h
#include <pthread.h>
#define NUM_CLIENTES 10  

class Mutex {
public:
	Mutex() {}
	~Mutex() {} 
	void lock() { pthread_mutex_lock(&mut); }
	void unlock()   {pthread_mutex_unlock(&mut);} 
	void CCliente() {pthread_cond_signal(&cond_cliente);}
	void CBarbeiro(){pthread_cond_signal(&cond_barbeiro); } 
	void WCliente(int m) {pthread_cond_wait(&cond_cliente, &mutC[m]);}
	void WBarbeiro(){pthread_cond_wait(&cond_barbeiro, &mutB);} 
	void init(){  cond_cliente = PTHREAD_COND_INITIALIZER; 
	              cond_barbeiro = PTHREAD_COND_INITIALIZER; 
	              mutB = PTHREAD_MUTEX_INITIALIZER;
	              for(int i = 0; i < NUM_CLIENTES; i++ ) mutC[i] = PTHREAD_MUTEX_INITIALIZER;
}

private:
	pthread_mutex_t mut;
	pthread_mutex_t mutB;
	pthread_mutex_t mutC[NUM_CLIENTES];
	pthread_cond_t cond_barbeiro;
	pthread_cond_t cond_cliente;
}; 
#endif
