#ifndef __PTHREAD_RWLOCK_H__
#define __PTHREAD_RWLOCK_H__

#include <rtthread.h>
#include <pthread.h>
#include <sys/time.h>

struct pthread_rwlock
{
	pthread_rwlockattr_t attr;

	struct rt_semaphore wrlock;
	struct rt_semaphore rdlock;
};
typedef struct pthread_rwlock pthread_rwlock_t;

int pthread_rwlockattr_init (pthread_rwlockattr_t *attr);
int pthread_rwlockattr_destroy (pthread_rwlockattr_t *attr);
int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr, int *pshared);
int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *attr, int pshared);

int pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_destroy (pthread_rwlock_t *rwlock);

int pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);

int pthread_rwlock_timedrdlock (pthread_rwlock_t *rwlock, const struct timespec *abstime);
int pthread_rwlock_timedwrlock (pthread_rwlock_t *rwlock, const struct timespec *abstime);

int pthread_rwlock_unlock (pthread_rwlock_t *rwlock);

int pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);

#endif
