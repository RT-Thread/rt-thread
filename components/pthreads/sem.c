#include <errno.h>
#include <sys/fcntl.h>

#include "sem.h"

int sem_close(sem_t *sem)
{
}

int sem_destroy(sem_t *sem)
{
}

int sem_unlink(const char *name)
{
	return EACCES;
}

int sem_getvalue(sem_t *sem, int *sval)
{
	RT_ASSERT(sem != RT_NULL);
	if (sval) *sval = sem->value;
}

int sem_init(sem_t *sem, int pshared, unsigned int value)
{
	RT_ASSERT(sem != RT_NULL);
}

sem_t *sem_open(const char *name, int oflag, ...)
{
	rt_sem_t sem;

	sem = RT_NULL;
	if (oflag == O_CREAT)
	{
		sem = rt_sem_create(name, 1, RT_IPC_FLAG_FIFO);
		if (sem == RT_NULL)
			rt_set_errno(ENOSPC);
	}

	if (oflag == O_EXCL)
	{
		rt_enter_critical();
		/* find semaphore object */
		rt_exit_critical();

		if (sem == RT_NULL) rt_set_errno(ENOENT);
	}

	return sem;
}

int sem_post(sem_t *sem)
{
	rt_sem_release(sem);
}

int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
{
	rt_err_t result;
	rt_int32_t tick;

	if (!sem || !abs_timeout) return EINVAL;

	/* calculate os tick */
	tick = abs_timeout->tv_sec/RT_TICK_PER_SECOND + (abs_timeout->tv_nsec/1000) * (1000/RT_TICK_PER_SECOND);
	
	result = rt_sem_take(sem, tick);
	if (result == -RT_ETIMEOUT) return ETIMEDOUT;
	if (result == RT_EOK) return 0;

	return EINTR;
}

int sem_trywait(sem_t *sem)
{
	rt_err_t result;

	if (!sem) return EINVAL;

	result = rt_sem_take(sem, RT_WAITING_FOREVER);
	if (result == -RT_ETIMEOUT) return EAGAIN;
	if (result == RT_EOK) return 0;

	return EINTR;
}

int sem_wait(sem_t *sem)
{
	rt_err_t result;

	result = rt_sem_take(sem, RT_WAITING_FOREVER);
	if (result == RT_EOK) return 0;

	return EINTR;
}

