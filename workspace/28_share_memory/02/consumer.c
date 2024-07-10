/*
 * \File
 * consumer.c
 * \Brief
 *
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
	FILE *fp_out = NULL;
	frame_t frame;
	int frame_cnt = 0;

	int sem_id; // semaphore id
	int sem_id2;// semaphore id2

	int shm_id; // shared-memory id
	void *shared_memory = (void *)0;
	shared_use_st *shared_stuff;
	int end_flag = 0;

	/* Open output file */
	if ((fp_out = fopen(OUTPUT_FILE, "wb")) < 0)
	{
		printf("Open output file failed: %s\n", OUTPUT_FILE);
		exit(EXIT_FAILURE);
	}

	/* Init frame */
	init_frame(&frame, FYUV_WIDTH, FYUV_HEIGHT, YUV420);
	printf("FRAME: w = %d, h = %d\n", frame.frm_w, frame.frm_h);

	/* Create semaphore */
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

	printf("FRAME_CNT: %d\n", frame_cnt);
	/*
	 * 必须先置0,
	 * 否则会因生产者进程的异常退出未释放信号量而导致程序出错
	 */
	set_semvalue(sem_id, 0);
	set_semvalue(sem_id2, 0);

	while (1)
	{
		semaphore_p(sem_id2);

		/* Read frame from shared-memory */
		read_frame_from_shm(&frame, shared_stuff);
		end_flag = shared_stuff->end_flag;
		if (end_flag)
		{
			semaphore_v(sem_id);
			break;
		}
		crop_frame(&frame, 10, 10, 40, 40);
		write_frame_into_file(fp_out, &frame);
		semaphore_v(sem_id);

		frame_cnt++;
		printf("FRAME_CNT: %d\n", frame_cnt);
	}

	/* Over */
	printf("\nConsumer over!\n");
	fclose(fp_out);
	free_frame(&frame);
	if (shmdt(shared_memory) == -1)
	{
		fprintf(stderr, "shmdt failed.\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

/*
消费者进程的基本流程:
打开输出文件并初始化帧;
获取共享内存和信号量;
每次
  得到共享内存的权限后，
  从共享内存中读取一帧并获得结束标志
  进行帧处理，
  释放共享内存的权限。
直到结束标志为真。

最后释放相关的资源。
*/