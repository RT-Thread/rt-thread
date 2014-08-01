#include <reent.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef RT_USING_PTHREADS 
#include <pthread.h>
#endif

/* Reentrant versions of system calls.  */

int
_close_r(struct _reent *ptr, int fd)
{
#ifndef RT_USING_DFS
	return 0;
#else
	return close(fd);
#endif
}

int
_execve_r(struct _reent *ptr, const char * name, char *const *argv, char *const *env)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_fork_r(struct _reent *ptr)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_getpid_r(struct _reent *ptr)
{
	return 0;
}

int
_isatty_r(struct _reent *ptr, int fd)
{
	if (fd >=0 && fd < 3) return 1;

	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_kill_r(struct _reent *ptr, int pid, int sig)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_link_r(struct _reent *ptr, const char *old, const char *new)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

_off_t
_lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
#ifndef RT_USING_DFS
	return 0;
#else
	_off_t rc;

	rc = lseek(fd, pos, whence);
	return rc;
#endif
}

int
_mkdir_r(struct _reent *ptr, const char *name, int mode)
{
#ifndef RT_USING_DFS
	return 0;
#else
	int rc;

	rc = mkdir(name, mode);
	return rc;
#endif
}

int
_open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
#ifndef RT_USING_DFS
	return 0;
#else
	int rc;

	rc = open(file, flags, mode);
	return rc;
#endif
}

_ssize_t 
_read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
#ifndef RT_USING_DFS
	return 0;
#else
	_ssize_t rc;

	rc = read(fd, buf, nbytes);
	return rc;
#endif
}

int
_rename_r(struct _reent *ptr, const char *old, const char *new)
{
#ifndef RT_USING_DFS
	return 0;
#else
	int rc;

	rc = rename(old, new);
	return rc;
#endif
}

void *
_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
	/* no use this routine to get memory */
	return RT_NULL;
}

int
_stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
#ifndef RT_USING_DFS
	return 0;
#else
	int rc;

	rc = stat(file, pstat);
	return rc;
#endif
}

_CLOCK_T_
_times_r(struct _reent *ptr, struct tms *ptms)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_unlink_r(struct _reent *ptr, const char *file)
{
#ifndef RT_USING_DFS
	return 0;
#else
	int rc;

	rc = unlink(file);
	return rc;
#endif
}

int
_wait_r(struct _reent *ptr, int *status)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

#ifdef RT_USING_DEVICE
_ssize_t
_write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
	if (fd < 3)
	{
#ifdef RT_USING_CONSOLE
		rt_device_t console_device;
		extern rt_device_t rt_console_get_device(void);

		console_device = rt_console_get_device();
		if (console_device != 0) rt_device_write(console_device, 0, buf, nbytes);
		return nbytes;
#else
        return 0;
#endif
	}
	else
	{
#ifdef RT_USING_DFS
	    _ssize_t rc;

	    rc = write(fd, buf, nbytes);
	    return rc;
#else
        return 0;
#endif
	}
}
#endif

#ifndef RT_USING_PTHREADS

#ifndef MILLISECOND_PER_SECOND
#define MILLISECOND_PER_SECOND	1000UL
#endif

#ifndef MICROSECOND_PER_SECOND
#define MICROSECOND_PER_SECOND	1000000UL
#endif

#ifndef NANOSECOND_PER_SECOND
#define NANOSECOND_PER_SECOND	1000000000UL
#endif

#define MILLISECOND_PER_TICK	(MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK	(MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK		(NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)


struct timeval _timevalue = {0};
#ifdef RT_USING_DEVICE
static void libc_system_time_init(void)
{
	time_t time;
	rt_tick_t tick;
	rt_device_t device;

	time = 0;
	device = rt_device_find("rtc");
	if (device != RT_NULL)
	{
		/* get realtime seconds */
		rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
	}

	/* get tick */
	tick = rt_tick_get();

	_timevalue.tv_usec = MICROSECOND_PER_SECOND - (tick%RT_TICK_PER_SECOND) * MICROSECOND_PER_TICK;
	_timevalue.tv_sec = time - tick/RT_TICK_PER_SECOND - 1;
}
#endif

int libc_get_time(struct timespec *time)
{
	rt_tick_t tick;
	static rt_bool_t inited = 0;

	RT_ASSERT(time != RT_NULL);

	/* initialize system time */
	if (inited == 0)
	{
		libc_system_time_init();
		inited = 1;
	}

	/* get tick */
	tick = rt_tick_get();

	time->tv_sec = _timevalue.tv_sec + tick / RT_TICK_PER_SECOND;
	time->tv_nsec = (_timevalue.tv_usec + (tick % RT_TICK_PER_SECOND) * NANOSECOND_PER_TICK) * 1000;

	return 0;
}

int
_gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp)
{
	struct timespec tp;

	if (libc_get_time(&tp) == 0)
	{
		if (__tp != RT_NULL)
		{
			__tp->tv_sec  = tp.tv_sec;
			__tp->tv_usec = tp.tv_nsec * 1000UL;
		}

		return tp.tv_sec;
	}

	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}
#else
/* POSIX thread provides clock_gettime function */
#include <time.h>
int
_gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp)
{
	struct timespec tp;

	if (clock_gettime(CLOCK_REALTIME, &tp) == 0)
	{
		if (__tp != RT_NULL)
		{
			__tp->tv_sec  = tp.tv_sec;
			__tp->tv_usec = tp.tv_nsec * 1000UL;
		}

		return tp.tv_sec;
	}

	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}
#endif

/* Memory routine */
void *
_malloc_r (struct _reent *ptr, size_t size)
{
	void* result;

	result = (void*)rt_malloc (size);
	if (result == RT_NULL)
	{
		ptr->_errno = ENOMEM;
	}

	return result;
}

void *
_realloc_r (struct _reent *ptr, void *old, size_t newlen)
{
	void* result;

	result = (void*)rt_realloc (old, newlen);
	if (result == RT_NULL)
	{
		ptr->_errno = ENOMEM;
	}

	return result;
}

void *_calloc_r (struct _reent *ptr, size_t size, size_t len)
{
	void* result;

	result = (void*)rt_calloc (size, len);
	if (result == RT_NULL)
	{
		ptr->_errno = ENOMEM;
	}

	return result;
}

void 
_free_r (struct _reent *ptr, void *addr)
{
	rt_free (addr);
}

void
_exit (int status)
{
#ifdef RT_USING_MODULE
	rt_module_t module;

	module = rt_module_self();
	if (module != RT_NULL)
	{
		struct rt_list_node *list;
		struct rt_object *object;

		rt_enter_critical();
		
        /* delete all threads in the module */
        list = &module->module_object[RT_Object_Class_Thread].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_thread_detach((rt_thread_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_thread_delete((rt_thread_t)object);
            }
        }
		/* delete main thread */
		rt_thread_delete(module->module_thread);
		rt_exit_critical();

		/* re-schedule */
		rt_schedule();
	}
#endif
	
	rt_kprintf("thread:%s exit with %d\n", rt_thread_self()->name, status);
	RT_ASSERT(0);

	while (1);
}

void 
_system(const char *s)
{
    /* not support this call */
    return;
}
