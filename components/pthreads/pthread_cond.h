#ifndef __PTHREAD_COND_H__
#define __PTHREAD_COND_H__

#include <pthread.h>
#include <sys/time.h>

struct pthread_cond
{
	pthread_mutex_t *mutex;
};
typedef struct pthread_cond pthread_cond_t;

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond,
	pthread_mutex_t * mutex,
	const struct timespec *abstime);

#endif
