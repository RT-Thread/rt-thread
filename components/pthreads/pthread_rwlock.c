#include "pthread_rwlock.h"

int pthread_rwlockattr_init (pthread_rwlockattr_t * attr)
{
	if (!attr) return EINVAL;
	*attr = PTHREAD_PROCESS_PRIVATE;

	return 0;
}

int pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr)
{
	if (!attr) return EINVAL;

	return 0;
}

int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t * attr, int *pshared)
{
	if (!attr || !pshared) return EINVAL;

	*pshared = PTHREAD_PROCESS_PRIVATE;
	return 0;
}

int pthread_rwlockattr_setpshared (pthread_rwlockattr_t * attr, int pshared)
{
	if (!attr || pshared != PTHREAD_PROCESS_PRIVATE) return EINVAL;

	return 0;
}

int pthread_rwlock_init (pthread_rwlock_t * rwlock, const pthread_rwlockattr_t * attr)
{
	return 0;
}

int pthread_rwlock_destroy (pthread_rwlock_t * rwlock)
{
	return 0;
}

int pthread_rwlock_rdlock (pthread_rwlock_t * rwlock)
{
	return 0;
}

int pthread_rwlock_tryrdlock (pthread_rwlock_t * rwlock)
{
	if (!rwlock) return EINVAL;
	return 0;
}

int pthread_rwlock_timedrdlock (pthread_rwlock_t * rwlock, const struct timespec *abstime)
{
	if (!rwlock) return EINVAL;
	return 0;
}

int pthread_rwlock_timedwrlock (pthread_rwlock_t * rwlock, const struct timespec *abstime)
{
	if (!rwlock) return EINVAL;
	return 0;
}

int pthread_rwlock_trywrlock (pthread_rwlock_t * rwlock)
{
	if (!rwlock) return EINVAL;
	return 0;
}

int pthread_rwlock_unlock (pthread_rwlock_t * rwlock)
{
	if (!rwlock) return EINVAL;

	return 0;
}

int pthread_rwlock_wrlock (pthread_rwlock_t * rwlock)
{
	return 0;
}
