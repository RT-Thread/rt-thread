/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <string.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <rtthread.h>
#include <limits.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include "mqueue.h"

static rt_list_t _mqueue_file_list = RT_LIST_OBJECT_INIT(_mqueue_file_list);
struct rt_spinlock mqueue_lock;

struct mqueue_file *dfs_mqueue_lookup(const char       *path,
                                      rt_size_t        *size)
{
    struct mqueue_file *file;
    rt_list_t *node;
    rt_spin_lock(&mqueue_lock);
    rt_list_for_each(node, &_mqueue_file_list)
    {
        file = rt_list_entry(node, struct mqueue_file, list);

        if (rt_strncmp(file->name, path, RT_NAME_MAX) == 0)
        {
            *size = file->size;
            rt_spin_unlock(&mqueue_lock);
            return file;
        }
    }
    rt_spin_unlock(&mqueue_lock);
    return RT_NULL;
}

int dfs_mqueue_mount(struct dfs_filesystem *fs,
                    unsigned long          rwflag,
                    const void            *data)
{
    return RT_EOK;
}

int dfs_mqueue_unmount(struct dfs_filesystem *fs)
{
    return RT_EOK;
}

int dfs_mqueue_statfs(struct dfs_filesystem *fs, struct statfs *buf)
{
    return RT_EOK;
}

int dfs_mqueue_close(struct dfs_file *file)
{
    return RT_EOK;
}

int dfs_mqueue_open(struct dfs_file *file)
{
    rt_size_t size;
    if ((file->vnode->path[0] == '/') && (file->vnode->path[1] == '\0'))
        return 0;

    if (file->flags & O_DIRECTORY)
        return -ENOENT;

    struct mqueue_file *mq_file;

    mq_file = dfs_mqueue_lookup(file->vnode->path + 1, &size);
    if (mq_file == RT_NULL && !(file->flags & O_CREAT))
        return -ENOENT;
    if (mq_file == RT_NULL)
    {
        mq_file = (struct mqueue_file *) rt_malloc (sizeof(struct mqueue_file));
        if (mq_file == RT_NULL)
        {
            return -ENFILE;
        }
        mq_file->msg_size = 8192;
        mq_file->max_msgs = 10;
        strncpy(mq_file->name, file->vnode->path + 1, RT_NAME_MAX);
        rt_list_init(&(mq_file->list));
        rt_spin_lock(&mqueue_lock);
        rt_list_insert_after(&(_mqueue_file_list), &(mq_file->list));
        rt_spin_unlock(&mqueue_lock);
    }

    if (file->flags & O_CREAT)
    {
        rt_mq_t mq = rt_mq_create(file->vnode->path + 1, mq_file->msg_size, mq_file->max_msgs, RT_IPC_FLAG_FIFO);
        mq_file->data = (void *)mq;
        file->vnode->data = mq_file;
        file->vnode->size = 0;
    }

    return 0;
}

int dfs_mqueue_stat(struct dfs_filesystem *fs,
                   const char            *path,
                   struct stat           *st)
{
    st->st_dev = 0;
    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                  S_IWUSR | S_IWGRP | S_IWOTH;
    st->st_size = 0;
    st->st_mtime = 0;
    return RT_EOK;
}

int dfs_mqueue_getdents(struct dfs_file *file,
                       struct dirent *dirp,
                       uint32_t    count)
{
    rt_size_t index, end;
    struct dirent *d;
    count = (count / sizeof(struct dirent));
    end = file->pos + count;
    index = 0;
    count = 0;
    struct mqueue_file *mq_file;
    rt_list_t *node;
    rt_spin_lock(&mqueue_lock);
    rt_list_for_each(node, &_mqueue_file_list)
    {
        if (index >= (rt_size_t)file->pos)
        {
            mq_file = rt_list_entry(node, struct mqueue_file, list);
            d = dirp + count;
            d->d_namlen = RT_NAME_MAX;
            d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(d->d_name, mq_file->name, RT_NAME_MAX);
            count += 1;
            file->pos += 1;
        }
        index += 1;
        if (index >= end)
        {
            break;
        }
    }
    rt_spin_unlock(&mqueue_lock);
    return count * sizeof(struct dirent);
}

int dfs_mqueue_unlink(struct dfs_filesystem *fs, const char *path)
{
    rt_size_t size;
    struct mqueue_file *mq_file;
    mq_file = dfs_mqueue_lookup(path + 1, &size);
    if (mq_file == RT_NULL)
        return -ENOENT;
    rt_list_remove(&(mq_file->list));
    if (mq_file->data != RT_NULL)
        rt_mq_delete((rt_mq_t)mq_file->data);
    rt_free(mq_file);
    return RT_EOK;
}

static const struct dfs_file_ops _mqueue_fops =
{
    .open = dfs_mqueue_open,
    .close = dfs_mqueue_close,
    .getdents = dfs_mqueue_getdents,
};

static const struct dfs_filesystem_ops _mqueue =
{
    .name = "mqueue",
    .flags = DFS_FS_FLAG_DEFAULT,
    .fops = &_mqueue_fops,

    .mount = dfs_mqueue_mount,
    .unmount = dfs_mqueue_unmount,
    .statfs = dfs_mqueue_statfs,

    .unlink = dfs_mqueue_unlink,
    .stat = dfs_mqueue_stat,
};

int dfs_mqueue_init(void)
{
    /* register mqueue file system */
    dfs_register(&_mqueue);
    return 0;
}

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
        strncpy(mq_file->name, name, RT_NAME_MAX);
        rt_list_init(&(mq_file->list));
        rt_spin_lock(&mqueue_lock);
        rt_list_insert_after(&(_mqueue_file_list), &(mq_file->list));
        rt_spin_unlock(&mqueue_lock);
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
    char* mq_path = "/dev/mqueue/";
    char mq_name[strlen(mq_path) + RT_NAME_MAX];
    rt_sprintf(mq_name, "%s%s", mq_path, name);
    return unlink(mq_name);
}
RTM_EXPORT(mq_unlink);
