#ifndef __thread_h
#define __thread_h
#include <pthread.h>
#include <signal.h>
class Thread
{
public:
    Thread(int ( * const entry)(int), int arg) {
	if(pthread_create(&thread, 0, (void *(*)(void *))entry, (void *)arg))
	    thread = 0;
    }
    ~Thread() {}
    int join(int *status) { return pthread_join(thread, (void **)status); }
private:
    pthread_t thread;
};
#endif
