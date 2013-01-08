#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mqueue.h>

#define MQ_NAME_1       "testmsg1"
#define MQ_NAME_2       "testmsg2"
#define MSG_SIZE	128
#define MAX_MSG		3

const char *s_msg_ptr[] = {"msg test 1", "msg test 2", "msg test 3"};
char r_msg_ptr_1[MAX_MSG][MSG_SIZE];
char r_msg_ptr_2[MAX_MSG][MSG_SIZE];
pthread_t send1, send2, rev1, rev2;

int * send_1(void * mq) 
{
	int i;
	mqd_t mq1 = *(mqd_t *)mq;

	printf("Enter into send_1 \n");
	for (i = 0; i < MAX_MSG; i++ ) {
		if ( -1 == mq_send(mq1, s_msg_ptr[i], MSG_SIZE, i)) {
			perror("mq_send doesn't return success \n");
			pthread_exit((void *)1);
		}
		printf("[%d] send '%s' in thread send_1. \n", i+1, s_msg_ptr[i]);
	}
	pthread_exit((void *)0);

}

int * send_2(void * mq) 
{
	int i;
 	mqd_t mq2 = *(mqd_t *)mq;

	printf("Enter into send_2 \n");
	for (i = 0; i < MAX_MSG; i++ ) {
		if ( -1 == mq_send(mq2, s_msg_ptr[i], MSG_SIZE, i)) {
			perror("mq_send doesn't return success \n");
			pthread_exit((void *)1);
		}
		printf("[%d] send '%s' in thread send_2. \n", i+1, s_msg_ptr[i]);
	}
	pthread_exit((void *)0);
}

int * receive_1(void * mq) 
{
	int i;
	mqd_t mq1 = *(mqd_t *)mq;

	printf("Enter into receive_1 \n");
	for (i = 0; i< MAX_MSG; i++) {
		if ( -1 == mq_receive(mq1, r_msg_ptr_1[i], MSG_SIZE, NULL) ) {
			perror("mq_receive doesn't return success \n");
			pthread_exit((void *)1);
		}
		printf("[%d] receive '%s' in thread receive_1. \n", i+1, r_msg_ptr_1[i]);
	}
	pthread_exit((void *)0);
}
int * receive_2(void * mq) 
{
	int i;
	mqd_t mq2 = *(mqd_t *)mq;

	printf("Enter into receive_2 \n");
	for (i = 0; i< MAX_MSG; i++) {
		if ( -1 == mq_receive(mq2, r_msg_ptr_2[i], MSG_SIZE, NULL) ) {
			perror("mq_receive doesn't return success \n");
			pthread_exit((void *)1);
		}
		printf("[%d] receive '%s' in thread receive_2. \n", i+1, r_msg_ptr_2[i]);
	}
	pthread_exit((void *)0);
}

int libc_mq()
{
 	mqd_t mq1 = 0, mq2 = 0;	
	struct mq_attr mqstat;
	int oflag = O_CREAT|O_RDWR;

	memset(&mqstat, 0, sizeof(mqstat));
	mqstat.mq_maxmsg = MAX_MSG;
	mqstat.mq_msgsize = MSG_SIZE;
	mqstat.mq_flags = 0;
  
  	if( ((mqd_t) -1) == (mq1 = mq_open(MQ_NAME_1,oflag,0777, &mqstat)) ) {
		printf("mq_open doesn't return success \n");
		return -1;
	}
  	if( ((mqd_t) -1) == (mq2 = mq_open(MQ_NAME_2,oflag,0777, &mqstat)) ) {
		printf("mq_open doesn't return success \n");
		return -1;
	}
	pthread_create(&send1, NULL, (void *)send_1, (void *)&mq1);
	pthread_create(&send2, NULL, (void *)send_2, (void *)&mq2);
        pthread_create(&rev1, NULL, (void *)receive_1, (void *)&mq1);	
        pthread_create(&rev2, NULL, (void *)receive_2, (void *)&mq2);	
	pthread_join(send1, NULL);
	pthread_join(send2, NULL);
	pthread_join(rev1, NULL);
	pthread_join(rev2, NULL);
		
	mq_close(mq1);
	mq_close(mq2);
	mq_unlink(MQ_NAME_1);
	mq_unlink(MQ_NAME_2);

	printf("PASSED\n");
	return 0;
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_mq, posix mqueue test);
