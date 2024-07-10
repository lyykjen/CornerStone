/*
 * \File
 * shm_com.h
 * \Brief
 *共享内存相关的头文件。
 */
#ifndef __SHM_COM_H__
#define __SHM_COM_H__

#define SHM_SEED 1001
#define MAX_SHM_SIZE 1920*1080*3/2

typedef struct shared_use_st
{
	int end_flag;              //用来标记进程间的内存共享是否结束: 0, 未结束； 1， 结束
	char shm_sp[MAX_SHM_SIZE]; //共享内存的空间
} shared_use_st;

#endif