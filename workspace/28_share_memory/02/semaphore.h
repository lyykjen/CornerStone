/*
 * \File
 * semaphore.h
 * \Brief
 * semaphore operation
 *信号量的头文件
 */
#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#define SEM_SEED 1000
#define SEM2_SEED 2000

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int set_semvalue(int sem_id, int value);
void del_semvalue(int sem_id);
int semaphore_p(int sem_id);
int semaphore_v(int sem_id);

#endif