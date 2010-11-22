#include <pthread.h>
#include <mqueue.h>
#include <sys/fcntl.h>

void child(void* parameter)
{
	char msg[16];
	ssize_t len;
	mqd_t mq;
	int i;
	char expect;
	
	printf("Child here!\n");
	
	if((mq = mq_open("Q001", O_RDONLY, 0, 0)) == -1)
	{
		printf("mq_open = %d\n", errno);
		pthread_exit(0);
	}
	else printf("mq = %x\n", &mq);

	for(expect = 'V'; expect <= 'Z'; ++expect)
	{
		memset(msg, 0, sizeof(msg));
		printf("Child waiting...\n");
		if((len = mq_receive(mq, msg, sizeof(msg), 0)) == -1)
		{
			printf("mq_receive = %d\n", errno);
			pthread_exit(0);
		}
		else printf("GOT MESSAGE %c!\n", expect);

		if(len != 8)
			printf("expected len 8 got %d\n", len);
		
		for(i = 0; i < 8; ++i)
			if(msg[i] != expect)
				printf("msg[%d] got %c expected %c\n", i, msg[i], expect);
	}
	
	if(mq_close(mq) == -1)
		printf("mq_close failed\n");
			
	printf("child done\n");
	pthread_exit(0);
}


void send(void* parameter)
{
	mqd_t mq;
	char msg[8];

	printf("Send here!\n");

	if((mq = mq_open("Q001", O_WRONLY, 0, 0)) == -1)
	{
		printf("mq_open = %d\n", errno);
		pthread_exit(0);
	}	
	else printf("mq = %x\n", &mq);

	/* task will be blocked waiting for message */	
	memset(msg, 'Z', 8);
	if(mq_send(mq, msg, 8, 0) == -1)
		printf("mq_send = %d\n", errno);

	if(mq_close(mq) == -1)
		printf("mq_close failed\n");

	printf("Send done\n");
	pthread_exit(0);
}

void test_thread(void* parameter)
{
	struct mq_attr attr;
	mqd_t mq;
	char msg[8];
	pthread_t pthrId; 
	
	printf("Main here!\n");

	attr.mq_flags	= 0;
	attr.mq_maxmsg	= 3;
	attr.mq_msgsize	= 16;
	if((mq = mq_open("Q001", O_CREAT | O_RDWR, 0, &attr)) == -1)
	{
		printf("mq_open = %d\n", errno);
		pthread_exit(0);
	}
	else printf("mq = %x\n", &mq);
	
	memset(msg, 'V', 8);
	if(mq_send(mq, msg, 8, 0) == -1)
		printf("mq_send = %d\n", errno);

	memset(msg, 'W', 8);
	if(mq_send(mq, msg, 8, 0) == -1)
		printf("mq_send = %d\n", errno);

	memset(msg, 'X', 8);
	if(mq_send(mq, msg, 8, 0) == -1)
		printf("mq_send = %d\n", errno);

	if(pthread_create(&pthrId, 0, &child, 0)!=0)
	{
		printf("pthread_create Child = %d\n", errno);
		pthread_exit(0);
	}

	/* Should block */
	printf("send Y\n");
	memset(msg, 'Y', 8);
	if(mq_send(mq, msg, 8, 0) == -1)
		printf("mq_send = %d\n", errno);
	else printf("sent Y\n");

	if(pthread_create(&pthrId, 0, send, 0)!=0)
	{
		printf("pthread_create Send = %d\n", errno);
		pthread_exit(0);
	}

	if(mq_close(mq) == -1)
		printf("mq_close failed\n");

	printf("main done\n");
	pthread_exit(0);
}

#include <finsh.h>
void libc_mq()
{
	rt_thread_t tid;

	tid = rt_thread_create("mqtest", test_thread, RT_NULL, 
		2048, 20, 5);
	if (tid != RT_NULL)
	{
		rt_thread_startup(tid);
	}
}
FINSH_FUNCTION_EXPORT(libc_mq, mqueue test);
