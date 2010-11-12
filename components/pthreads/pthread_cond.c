#include "pthread_cond.h"

int pthread_condattr_getpshared(const pthread_condattr_t *attr, int *pshared)
{
	if (!attr || !pshared) return EINVAL;

	*pshared = PTHREAD_PROCESS_PRIVATE;
	return 0;
}

int pthread_condattr_setpshared(pthread_condattr_t*attr, int pshared)
{
	if ((pshared != PTHREAD_PROCESS_PRIVATE) && (pshared != PTHREAD_PROCESS_SHARED))
    	return EINVAL;

	if (pshared != PTHREAD_PROCESS_PRIVATE)
    	return ENOSYS;

	return 0;
}

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr)
{
	/* parameter check */
	if (cond == RT_NULL) return EINVAL;
	if ((attr != RT_NULL) && (*attr != PTHREAD_PROCESS_PRIVATE)) return EINVAL;

	return 0;
}

int pthread_cond_destroy(pthread_cond_t *cond)
{
	return 0;
}

int pthread_cond_broadcast(pthread_cond_t *cond)
{
	return 0;
}

int pthread_cond_signal(pthread_cond_t *cond)
{
	return 0;
}

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
	return 0;
}

int pthread_cond_timedwait(pthread_cond_t *cond,
	pthread_mutex_t * mutex,
	const struct timespec *abstime)
{
	return 0;
}

