#ifndef __MAIN_H__
#define __MAIN_H__
#include <pthread.h>

extern int cnt;
extern pthread_cond_t cond;
extern pthread_mutex_t mutex;
extern int flag;
extern pthread_t thread;
void fun();

typedef struct {
	int a;
	char b;
	float c;
}handle_data_t;

extern handle_data_t msg;
#endif