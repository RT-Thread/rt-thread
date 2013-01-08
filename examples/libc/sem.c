#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

static sem_t sema;
static void* other_thread()
{
	printf("other_thread here!\n");

	sleep(1);

	while (1)
	{
		printf("other_thread: sem_post...\n");
		if(sem_post(&sema) == -1)
			printf("sem_post failed\n");
		sleep(1);
	}
	
	printf("other_thread dies!\n");
	pthread_exit(0);
}

static void test_thread(void* parameter)
{
	pthread_t tid;

	printf("main thread here!\n");
	printf("sleep 5 seconds...");	
	sleep(5);
	printf("done\n");

	sem_init(&sema, 0, 0);
	
	/* create the "other" thread */
	if(pthread_create(&tid, 0, &other_thread, 0)!=0)
		/* error */
		printf("pthread_create OtherThread failed.\n");
	else
		printf("created OtherThread=%x\n", tid);

	/* let the other thread run */
	while (1)
	{
		printf("Main: sem_wait...\n");
		if(sem_wait(&sema) == -1)
			printf("sem_wait failed\n");
		printf("Main back.\n\n");
	}

	pthread_exit(0);
}
#include <finsh.h>
void libc_sem()
{
	rt_thread_t tid;

	tid = rt_thread_create("semtest", test_thread, RT_NULL, 
		2048, 20, 5);
	if (tid != RT_NULL)
	{
		rt_thread_startup(tid);
	}
}
FINSH_FUNCTION_EXPORT(libc_sem, posix semaphore test);
