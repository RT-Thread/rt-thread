#include <pthread.h>

int pthread_spin_init (pthread_spinlock_t *lock, int pshared)
{
	if (!lock) return EINVAL;

	lock->lock = 0;
	return 0;
}

int pthread_spin_destroy (pthread_spinlock_t *lock)
{
	if (!lock) return EINVAL;

	return 0;
}

int pthread_spin_lock (pthread_spinlock_t *lock)
{
	if (!lock) return EINVAL;

	while (!(lock->lock))
	{
		lock->lock = 1;
	}

	return 0;
}

int pthread_spin_trylock (pthread_spinlock_t *lock)
{
	if (!lock) return EINVAL;

	if (!(lock->lock))
	{
		lock->lock = 1;
		return 0;
	}

	return EBUSY;
}

int pthread_spin_unlock (pthread_spinlock_t *lock)
{
	if (!lock) return EINVAL;
	if (!(lock->lock)) return EPERM;

	lock->lock = 0;

	return 0;
}
