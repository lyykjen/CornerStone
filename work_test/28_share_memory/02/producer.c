/*
 * \File
 * producer.c
 * \Brief
 * Test shared-memory and message-queue
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/shm.h>
#include <sys/sem.h>

#include "common.h"
#include "semaphore.h"
#include "shm_com.h"
#include "frame.h"

int main(int argc, char *argv[])
{
	FILE *fp_in = NULL;
	frame_t frame;
	int frame_cnt = 0;

	int sem_id; // semaphore id
	int sem_id2;// semaphore id2

	int shm_id; // shared-memory id
	void *shared_memory = (void *)0;
	shared_use_st *shared_stuff;

	/* Open input file */
	if ((fp_in = fopen(TEST_FILE, "rb")) < 0)
	{
		printf("Open input file failed: %s\n", TEST_FILE);
		exit(EXIT_FAILURE);
	}

	/* Init frame */
	init_frame(&frame, FYUV_WIDTH, FYUV_HEIGHT, YUV420);
	printf("FRAME: w = %d, h = %d\n", frame.frm_w, frame.frm_h);

	/* Create and init semaphore */
	sem_id = semget((key_t)SEM_SEED, 1, 0666 | IPC_CREAT);
	if (sem_id == -1)
	{
		fprintf(stderr, "semget failed.\n");
		exit(EXIT_FAILURE);
	}

	/* Create and init semaphore2 */
	sem_id2 = semget((key_t)SEM2_SEED, 1, 0666 | IPC_CREAT);
	if (sem_id2 == -1)
	{
		fprintf(stderr, "semget failed.\n");
		exit(EXIT_FAILURE);
	}

	/* Init shared-memory */
	shm_id = shmget((key_t)SHM_SEED, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shm_id == -1)
	{
		fprintf(stderr, "shmget failed.\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shm_id, (void *)0, 0);
	if (shared_memory == (void *) - 1)
	{
		fprintf(stderr, "shmat failed.\n");
		exit(EXIT_FAILURE);
	}

	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->end_flag = 0;

	printf("FRAME_CNT: %d\n", frame_cnt);
	set_semvalue(sem_id, 1);
	set_semvalue(sem_id2, 0);

	while (1)
	{
		semaphore_p(sem_id);
		if (!read_frame_from_file(&frame, fp_in))
		{
			shared_stuff->end_flag = 1;
			semaphore_v(sem_id2);
			break;
		}

		/* Write it into shared memory */
		write_frame_into_shm(shared_stuff, &frame);
		shared_stuff->end_flag = 0;
		semaphore_v(sem_id2);

		frame_cnt++;
		printf("FRAME_CNT: %d\n", frame_cnt);
	}


	/* over */
	printf("\nProducer over!\n");
	fclose(fp_in);
	free_frame(&frame);
	del_semvalue(sem_id);
	del_semvalue(sem_id2);
	if (shmdt(shared_memory) == -1)
	{
		fprintf(stderr, "shmdt failed.\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}


/*
 生产者进程的基本流程:
打开输入文件并初始化帧;
创建并初始化共享内存和信号量;
然后每次读取一帧，
  用信号量获取共享内存的权限后，
  将读取的帧写入共享内存，
  再释放共享内存的权限。
当处理完所有的帧后，
设置结束标志，
并释放相关的资源。
*/