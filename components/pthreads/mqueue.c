#include "mqueue.h"
#include "pthread_internal.h"

#include <stdarg.h>
#include <errno.h>
#include <sys/fcntl.h>

int mq_setattr(mqd_t mqdes, const struct mq_attr *mqstat,
		struct mq_attr *omqstat)
{
	rt_set_errno(-RT_ERROR);
	return -1;
}

int mq_getattr(mqd_t mqdes, struct mq_attr *mqstat)
{
	if ((mqdes == RT_NULL) || mqstat == RT_NULL)
	{
		rt_set_errno(EBADF);
		return -1;
	}

	mqstat->mq_maxmsg = mqdes->max_msgs;
	mqstat->mq_msgsize = mqdes->msg_size;
	mqstat->mq_curmsgs = 0;
	mqstat->mq_flags = 0;

	return 0;
}

mqd_t mq_open(const char *name, int oflag, ...)
{
	rt_mq_t mq;
	va_list arg;
	mode_t mode;
	struct mq_attr *attr = RT_NULL;

	if (oflag & O_CREAT)
	{
	    va_start(arg, oflag);
	    mode = (mode_t) va_arg(arg, unsigned int);
	    attr = (struct mq_attr *) va_arg(arg, struct mq_attr *);
	    va_end(arg);

		mq = rt_mq_create(name, attr->mq_msgsize, attr->mq_maxmsg, RT_IPC_FLAG_FIFO);
		if (mq == RT_NULL) /* create failed */
		{
			rt_set_errno(ENFILE);
			return RT_NULL;
		}
	}

	if (oflag & O_EXCL)
	{
		mq = (rt_mq_t)rt_object_find(name, RT_Object_Class_MessageQueue);
		if (mq == RT_NULL) rt_set_errno(ENOSPC);
	}

	return mq;
}

ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio)
{
	rt_err_t result;

	if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	result = rt_mq_recv(mqdes, msg_ptr, msg_len, RT_WAITING_FOREVER);
	if (result == RT_EOK)
		return msg_len;

	rt_set_errno(EBADF);
	return -1;
}

int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio)
{
	rt_err_t result;

	if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}

	result = rt_mq_send(mqdes, msg_ptr, msg_len);
	if (result == RT_EOK)
		return 0;

	rt_set_errno(EBADF);
	return -1;
}

ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
	unsigned *msg_prio, const struct timespec *abs_timeout)
{
	int tick;
	rt_err_t result;

	if ((mqdes == RT_NULL) || (msg_ptr == RT_NULL))
	{
		rt_set_errno(EINVAL);
		return -1;
	}
	tick = libc_time_to_tick(abs_timeout);

	result = rt_mq_recv(mqdes, msg_ptr, msg_len, tick);
	if (result == RT_EOK) return msg_len;

	if (result == -RT_ETIMEOUT)
		rt_set_errno(ETIMEDOUT);
	else
		rt_set_errno(EBADMSG);

	return -1;
}

int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio,
		const struct timespec *abs_timeout)
{
	/* RT-Thread does not support timed send */
	return mq_send(mqdes, msg_ptr, msg_len, msg_prio);
}

int mq_notify(mqd_t mqdes, const struct sigevent *notification)
{
	rt_set_errno(-RT_ERROR);
	return -1;
}

int mq_close(mqd_t mqdes)
{
	return 0;
}

int mq_unlink(const char *name)
{
	rt_mq_t mq;

	mq = (rt_mq_t)rt_object_find(name, RT_Object_Class_MessageQueue);
	if (mq == RT_NULL)
	{
		rt_set_errno(ENOENT);
		return -1;
	}

	/* delete this message queue */
	rt_mq_delete(mq);
	return 0;
}
