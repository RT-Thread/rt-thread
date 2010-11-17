#include <errno.h>
#include <sys/fcntl.h>

#include <rtthread.h>
#include "semaphore.h"

int sem_close(sem_t *sem)
{
	if (!sem) return EINVAL;

	/* delete semaphore allocated in sem_open */
	rt_sem_delete(sem);
	return 0;
}

int sem_destroy(sem_t *sem)
{
	rt_err_t result;

	if (!sem) return EINVAL;

	/* check whether semaphore is busy or not */
	result = rt_sem_trytake(sem);
	if (result != RT_EOK) return EBUSY;

	rt_memset(sem, 0, sizeof(sem_t));
	return 0;
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
	rt_err_t result;
	char name[RT_NAME_MAX];
	static rt_uint16_t psem_number = 0;

	RT_ASSERT(sem != RT_NULL);

	rt_snprintf(name, sizeof(name), "psem%02d", psem_number++);
	result = rt_sem_init(sem, name, value, RT_IPC_FLAG_FIFO);
	if (result == RT_EOK)
	{
		/* detach kernel object */
		rt_object_detach(&(sem->parent.parent));
		return 0;
	}

	return ENOSPC;
}

/* introduce from kservice.c */
#define rt_list_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))

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

	/* find semaphore */
	if (oflag == O_EXCL)
	{
		struct rt_object* object;
		struct rt_list_node* node;
		struct rt_object_information *information;
		extern struct rt_object_information rt_object_container[];

		/* enter critical */
		rt_enter_critical();

		/* try to find device object */
		information = &rt_object_container[RT_Object_Class_Semaphore];
		for (node = information->object_list.next; node != &(information->object_list); node = node->next)
		{
			object = rt_list_entry(node, struct rt_object, list);
			if (rt_strncmp(object->name, name, RT_NAME_MAX) == 0)
			{
				/* leave critical */
				rt_exit_critical();

				return (rt_sem_t)object;
			}
		}

		/* leave critical */
		rt_exit_critical();
		rt_set_errno(ENOENT);

		return RT_NULL;
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

