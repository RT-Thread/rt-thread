#ifndef __PTHREAD_COND_H__
#define __PTHREAD_COND_H__

#include <pthread.h>
#include <sys/time.h>
#include <rtthread.h>

struct pthread_cond
{
	pthread_condattr_t attr;
	struct rt_semaphore sem;
};
typedef struct pthread_cond pthread_cond_t;

int pthread_condattr_destroy(pthread_condattr_t *attr);
int pthread_condattr_init(pthread_condattr_t *attr);

/* ADVANCED REALTIME feature in IEEE Std 1003.1, 2004 Edition */
int pthread_condattr_getclock(const pthread_condattr_t *attr,
       clockid_t *clock_id);
int pthread_condattr_setclock(pthread_condattr_t *attr,
       clockid_t clock_id);

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond,
	pthread_mutex_t * mutex,
	const struct timespec *abstime);

#endif
