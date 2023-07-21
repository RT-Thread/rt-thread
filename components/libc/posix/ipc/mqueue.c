/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <dfs_file.h>
#include <unistd.h>
#include "mqueue.h"

int mq_setattr(mqd_t                 id,
               const struct mq_attr *mqstat,
               struct mq_attr       *omqstat)
{
    if (mqstat == RT_NULL)
        return mq_getattr(id, omqstat);
    else
        rt_set_errno(-RT_ERROR);

    return -1;
}
RTM_EXPORT(mq_setattr);

int mq_getattr(mqd_t id, struct mq_attr *mqstat)
{
    rt_mq_t mq;
    struct mqueue_file *mq_file;
    mq_file = fd_get(id)->vnode->data;
    mq = (rt_mq_t)mq_file->data;
    if ((mq == RT_NULL) || mqstat == RT_NULL)
    {
        rt_set_errno(EBADF);
        return -1;
    }

    mqstat->mq_maxmsg = mq->max_msgs;
    mqstat->mq_msgsize = mq->msg_size;
    mqstat->mq_curmsgs = 0;
    mqstat->mq_flags = 0;

    return 0;
}
RTM_EXPORT(mq_getattr);

mqd_t mq_open(const char *name, int oflag, ...)
{
    int mq_fd;
    va_list arg;
    mode_t mode;
    struct mq_attr *attr = RT_NULL;
    va_start(arg, oflag);
    mode = (mode_t)va_arg(arg, unsigned int);
    mode = (mode_t)mode; /* self-assignment avoids compiler optimization */
    attr = (struct mq_attr *)va_arg(arg, struct mq_attr *);
    attr = (struct mq_attr *)attr; /* self-assignment avoids compiler optimization */
    va_end(arg);
    if(*name == '/')
    {
        name++;
    }

    int len = rt_strlen(name);
    if (len > RT_NAME_MAX)
    {
        rt_set_errno(ENAMETOOLONG);
        return (mqd_t)(-1);
    }
    rt_size_t size;
    struct mqueue_file *mq_file;
    mq_file = dfs_mqueue_lookup(name, &size);
    if(mq_file != RT_NULL)
    {
        if (oflag & O_CREAT && oflag & O_EXCL)
        {
            rt_set_errno(EEXIST);
            return (mqd_t)(-1);
        }
    }
    else if (oflag & O_CREAT)
    {
        if (attr->mq_maxmsg <= 0)
        {
            rt_set_errno(EINVAL);
            return (mqd_t)(-1);
        }
        struct mqueue_file *mq_file;
        mq_file = (struct mqueue_file *) rt_malloc (sizeof(struct mqueue_file));

        if (mq_file == RT_NULL)
        {
            rt_set_errno(ENFILE);
            return (mqd_t)(-1);
        }
        mq_file->msg_size = attr->mq_msgsize;
        mq_file->max_msgs = attr->mq_maxmsg;
        mq_file->data = RT_NULL;
        strncpy(mq_file->name, name, RT_NAME_MAX);
        dfs_mqueue_insert_after(&(mq_file->list));
    }
    else
    {
        rt_set_errno(ENOENT);
        return (mqd_t)(-1);
    }

    const char* mq_path = "/dev/mqueue/";
    char mq_name[RT_NAME_MAX + 12] = {0};
    rt_sprintf(mq_name, "%s%s", mq_path, name);
    mq_fd = open(mq_name, oflag);

    return (mqd_t)(mq_fd);
}
RTM_EXPORT(mq_open);

ssize_t mq_receive(mqd_t id, char *msg_ptr, size_t msg_len, unsigned *msg_prio)
{
    rt_mq_t mq;
    rt_err_t result;
    struct mqueue_file *mq_file;
    mq_file = fd_get(id)->vnode->data;
    mq = (rt_mq_t)mq_file->data;
    if ((mq == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    result = rt_mq_recv_prio(mq, msg_ptr, msg_len, (rt_int32_t *)msg_prio, RT_WAITING_FOREVER, RT_UNINTERRUPTIBLE);
    if (result >= 0)
        return rt_strlen(msg_ptr);

    rt_set_errno(EBADF);
    return -1;
}
RTM_EXPORT(mq_receive);

int mq_send(mqd_t id, const char *msg_ptr, size_t msg_len, unsigned msg_prio)
{
    rt_mq_t mq;
    rt_err_t result;
    struct mqueue_file *mq_file;
    mq_file = fd_get(id)->vnode->data;
    mq = (rt_mq_t)mq_file->data;

    if ((mq == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    result = rt_mq_send_wait_prio(mq, (void *)msg_ptr, msg_len, msg_prio, 0, RT_UNINTERRUPTIBLE);
    if (result == RT_EOK)
        return 0;

    rt_set_errno(EBADF);

    return -1;
}
RTM_EXPORT(mq_send);

ssize_t mq_timedreceive(mqd_t                  id,
                        char                  *msg_ptr,
                        size_t                 msg_len,
                        unsigned              *msg_prio,
                        const struct timespec *abs_timeout)
{
    rt_mq_t mq;
    rt_err_t result;
    int tick = 0;
    struct mqueue_file *mq_file;
    mq_file = fd_get(id)->vnode->data;
    mq = (rt_mq_t)mq_file->data;
    /* parameters check */
    if ((mq == RT_NULL) || (msg_ptr == RT_NULL))
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    if (abs_timeout != RT_NULL)
        tick = rt_timespec_to_tick(abs_timeout);
    else
        tick = RT_WAITING_FOREVER;

    result = rt_mq_recv_prio(mq, msg_ptr, msg_len, (rt_int32_t *)msg_prio, tick, RT_UNINTERRUPTIBLE);

    if (result >= 0)
        return rt_strlen(msg_ptr);

    if (result == -RT_ETIMEOUT)
        rt_set_errno(ETIMEDOUT);
    else if (result == -RT_ERROR)
        rt_set_errno(EMSGSIZE);
    else
        rt_set_errno(EBADMSG);

    return -1;
}
RTM_EXPORT(mq_timedreceive);

int mq_timedsend(mqd_t                  id,
                 const char            *msg_ptr,
                 size_t                 msg_len,
                 unsigned               msg_prio,
                 const struct timespec *abs_timeout)
{
    /* RT-Thread does not support timed send */
    return mq_send(id, msg_ptr, msg_len, msg_prio);
}
RTM_EXPORT(mq_timedsend);

int mq_notify(mqd_t id, const struct sigevent *notification)
{
    rt_mq_t mq;
    struct mqueue_file *mq_file;
    mq_file = fd_get(id)->vnode->data;
    mq = (rt_mq_t)mq_file->data;
    if (mq == RT_NULL)
    {
        rt_set_errno(EBADF);
        return -1;
    }
    rt_set_errno(-RT_ERROR);

    return -1;
}
RTM_EXPORT(mq_notify);

int mq_close(mqd_t id)
{
    return close(id);
}
RTM_EXPORT(mq_close);

/**
 * @brief    This function will remove a message queue (REALTIME).
 *
 * @note    The mq_unlink() function shall remove the message queue named by the string name.
 *          If one or more processes have the message queue open when mq_unlink() is called,
 *          destruction of the message queue shall be postponed until all references to the message queue have been closed.
 *          However, the mq_unlink() call need not block until all references have been closed; it may return immediately.
 *
 *          After a successful call to mq_unlink(), reuse of the name shall subsequently cause mq_open() to behave as if
 *          no message queue of this name exists (that is, mq_open() will fail if O_CREAT is not set,
 *          or will create a new message queue if O_CREAT is set).
 *
 * @param    name  is the name of the message queue.
 *
 * @return   Upon successful completion, the function shall return a value of zero.
 *           Otherwise, the named message queue shall be unchanged by this function call,
 *           and the function shall return a value of -1 and set errno to indicate the error.
 *
 * @warning  This function can ONLY be called in the thread context, you can use RT_DEBUG_IN_THREAD_CONTEXT to
 *           check the context.
 *           The mq_unlink() function shall fail if:
 *              [EACCES]
 *              Permission is denied to unlink the named message queue.
 *              [EINTR]
 *              The call to mq_unlink() blocked waiting for all references to the named message queue to be closed and a signal interrupted the call.
 *              [ENOENT]
 *              The named message queue does not exist.
 *           The mq_unlink() function may fail if:
 *              [ENAMETOOLONG]
 *              The length of the name argument exceeds {_POSIX_PATH_MAX} on systems that do not support the XSI option
 *              or exceeds {_XOPEN_PATH_MAX} on XSI systems,or has a pathname component that is longer than {_POSIX_NAME_MAX} on systems that do
 *              not support the XSI option or longer than {_XOPEN_NAME_MAX} on XSI systems.A call to mq_unlink() with a name argument that contains
 *              the same message queue name as was previously used in a successful mq_open() call shall not give an [ENAMETOOLONG] error.
 */
int mq_unlink(const char *name)
{
    if(*name == '/')
    {
        name++;
    }
    const char *mq_path = "/dev/mqueue/";
    char mq_name[RT_NAME_MAX + 12] = {0};
    rt_sprintf(mq_name, "%s%s", mq_path, name);
    return unlink(mq_name);
}
RTM_EXPORT(mq_unlink);
