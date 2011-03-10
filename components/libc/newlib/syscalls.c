#include <reent.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <rtthread.h>

/* Reentrant versions of system calls.  */

int
_close_r(struct _reent *ptr, int fd)
{
	return close(fd);
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
	_off_t rc;

	rc = lseek(fd, pos, whence);
	return rc;
}

int
_mkdir_r(struct _reent *ptr, const char *name, int mode)
{
	int rc;

	rc = mkdir(name, mode);
	return rc;
}

int
_open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
	int rc;

	rc = open(file, flags, mode);
	return rc;
}

_ssize_t 
_read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = read(fd, buf, nbytes);
	return rc;
}

int
_rename_r(struct _reent *ptr, const char *old, const char *new)
{
	int rc;

	rc = rename(old, new);
	return rc;
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
	int rc;

	rc = stat(file, pstat);
	return rc;
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
	int rc;

	rc = unlink(file);
	return rc;
}

int
_wait_r(struct _reent *ptr, int *status)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

_ssize_t
_write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = write(fd, buf, nbytes);
	return rc;
}

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
static void libc_system_time_init()
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
	rt_kprintf("thread:%s exit with %d\n", rt_thread_self()->name, status);
    RT_ASSERT(0);
}
