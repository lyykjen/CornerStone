#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int pool_add_worker (void *(*process) (void *arg), void *arg);
void *thread_routine (void *arg);
void pool_init (int max_thread_num);
int pool_destroy ();