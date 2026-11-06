/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author              Notes
 * 2023-08-29       zmq810150896        first version
 * 2024-04-08       TroyMitchell        Add all function comments
 */

#include <rtthread.h>
#include <sys/signalfd.h>
#include <dfs_file.h>
#include <signal.h>
#include <rthw.h>
#include <sys/time.h>
#include <lwp_signal.h>
#include <lwp.h>
#include <lwp_internal.h>
#include <poll.h>
#include <rtdevice.h>

#define SIGNALFD_MUTEX_NAME "signalfd"
#define SIGINFO_MAX         10
#define SIGNALFD_SHARE_MAX  RT_SIGNALFD_MAX_NUM

struct rt_signalfd_ctx
{
    sigset_t sigmask;
    struct rt_mutex lock;
    siginfo_t info[SIGINFO_MAX];
    int sig_num;
    rt_wqueue_t signalfd_queue;
    struct rt_lwp *lwp[SIGNALFD_SHARE_MAX];
    int closing;                 /* set by close(); registration refuses afterwards */
    struct rt_work release_work; /* unlinks the listeners and frees the context */
};

static int signalfd_close(struct dfs_file *file);
static int signalfd_poll(struct dfs_file *file, struct rt_pollreq *req);
#ifndef RT_USING_DFS_V2
static ssize_t signalfd_read(struct dfs_file *file, void *buf, size_t count);
#else
static ssize_t signalfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos);
#endif
static int signalfd_add_notify(struct rt_signalfd_ctx *sfd);

/*
 * Lock order: LWP_LOCK(lwp) -> sfd->lock, never the reverse.
 *
 * lwp_signal_notify() walks lwp->signalfd_notify_head under LWP_LOCK and the
 * callback takes sfd->lock inside it. Registration takes LWP_LOCK of the
 * calling process and then sfd->lock, and does the lookup, the slot
 * assignment and the listener insertion in that one critical section, so a
 * slot is never visible without its listener and the lookup cannot go stale
 * between the check and the assignment. The process exit hook runs under
 * LWP_LOCK and takes sfd->lock the same way.
 *
 * Each registered process holds one LWP reference. The slot in sfd->lwp[] is
 * the registration: whoever clears a slot (the release work or the process
 * exit hook) drops that reference, so the pointer stays valid until cleared.
 *
 * close() is called by dfs_file_close() under the global DFS file lock, and
 * the process exit path takes that lock while it already holds LWP_LOCK
 * (__exit_files() under _resr_cleanup()). close() therefore never takes an
 * LWP lock: it marks the context closing, detaches it from the vnode and
 * hands the teardown to the system workqueue. The release work unlinks the
 * listeners under each process's own LWP_LOCK with no other lock held and
 * frees the context afterwards.
 *
 * The context is pinned by the descriptor the caller is operating on: read,
 * poll and the registration they perform assume that the same descriptor is
 * not closed concurrently by another thread, as the existing read/poll paths
 * already do. close() only tears the context down once the vnode reference
 * count has dropped to one.
 */

static const struct dfs_file_ops signalfd_fops = {
    .close = signalfd_close,
    .poll = signalfd_poll,
    .read = signalfd_read,
};

/**
 * @brief   Releases a closed signalfd context from the system workqueue.
 * @param   work    The release work embedded in the context.
 * @param   data    Pointer to the signalfd context.
 * @note    Runs with no lock held, so it may take each registered process's
 *          LWP_LOCK through lwp_signal_notify_remove_queue(). A process that
 *          exits before this runs has already cleared its own slot and
 *          dropped its reference through the exit hook.
 */
static void signalfd_release_work(struct rt_work *work, void *data)
{
    struct rt_signalfd_ctx *sfd = (struct rt_signalfd_ctx *)data;
    struct rt_lwp *lwps[SIGNALFD_SHARE_MAX];

    RT_UNUSED(work);

    /* take the slots over, then unlink the listeners outside sfd->lock */
    rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);
    for (int i = 0; i < SIGNALFD_SHARE_MAX; i++)
    {
        lwps[i] = sfd->lwp[i];
        sfd->lwp[i] = RT_NULL;
    }
    rt_mutex_release(&sfd->lock);

    for (int i = 0; i < SIGNALFD_SHARE_MAX; i++)
    {
        if (lwps[i])
        {
            /* the slot held a reference, so the process is still valid here */
            lwp_signal_notify_remove_queue(lwps[i], &sfd->signalfd_queue);
            lwp_ref_dec(lwps[i]);
        }
    }

    rt_mutex_detach(&sfd->lock);
    rt_free(sfd);
}

/**
 * @brief   Closes the file descriptor associated with a signalfd file.
 * @param   file    Pointer to the file structure.
 * @return  Upon successful completion, returns 0; otherwise, returns an error code.
 * @note    Called under the DFS file lock. Takes only sfd->lock; the listener
 *          teardown runs later from the system workqueue.
 */
static int signalfd_close(struct dfs_file *file)
{
    struct rt_signalfd_ctx *sfd;

    if (!file || !file->vnode)
    {
        return 0;
    }

    if (file->vnode->ref_count != 1)
    {
        return 0;
    }

    sfd = file->vnode->data;

    if (sfd)
    {
        rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);
        sfd->closing = 1;
        rt_mutex_release(&sfd->lock);

        file->vnode->data = RT_NULL;

        rt_work_init(&sfd->release_work, signalfd_release_work, sfd);
        rt_work_submit(&sfd->release_work, 0);
    }

    return 0;
}

/**
 * @brief   Adds a signalfd file descriptor to the poll queue and checks for pending events.
 * @param   file    Pointer to the file structure.
 * @param   req     Pointer to the poll request structure.
 * @return  The events that are ready on the file descriptor.
 */
static int signalfd_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    struct rt_signalfd_ctx *sfd;
    int events = 0;

    if (file->vnode)
    {
        sfd = file->vnode->data;

        if (signalfd_add_notify(sfd) < 0)
        {
            return POLLERR;
        }

        rt_poll_add(&sfd->signalfd_queue, req);

        rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);

        if (sfd->sig_num)
        {
            events |= POLLIN;
        }

        rt_mutex_release(&sfd->lock);
    }

    return events;
}

#ifndef RT_USING_DFS_V2
/**
 * @brief   Reads signals from a signalfd file descriptor.
 * @param   file    Pointer to the file structure.
 * @param   buf     Pointer to the buffer to store the signals.
 * @param   count   Maximum number of bytes to read.
 * @return  Upon successful completion, returns the number of bytes read; otherwise, returns an error code.
 */
static ssize_t signalfd_read(struct dfs_file *file, void *buf, size_t count)
#else
/**
 * @brief   Reads signals from a signalfd file descriptor with file offset.
 * @param   file    Pointer to the file structure.
 * @param   buf     Pointer to the buffer to store the signals.
 * @param   count   Maximum number of bytes to read.
 * @param   pos     Pointer to the file offset.
 * @return  Upon successful completion, returns the number of bytes read; otherwise, returns an negative error code.
 */
static ssize_t signalfd_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
#endif
{
    struct rt_signalfd_ctx *sfd = RT_NULL;
    struct signalfd_siginfo *buffer = RT_NULL;
    int user_buf_num = 0;
    int sig_num = 0;
    int i = 0;
    rt_err_t ret = -1;

    if (sizeof(struct signalfd_siginfo) > count)
    {
        return -1;
    }

    if (buf == RT_NULL)
    {
        return -1;
    }

    buffer = (struct signalfd_siginfo *)buf;
    user_buf_num = count / sizeof(struct signalfd_siginfo);

    if (file->vnode)
    {
        sfd = file->vnode->data;

        ret = signalfd_add_notify(sfd);
        if (ret < 0)
        {
            return ret;
        }

        if ((sfd->sig_num == 0) && (file->flags & O_NONBLOCK))
        {
            ret = -EAGAIN;
        }
        else
        {
            if (sfd->sig_num == 0)
            {
                rt_wqueue_wait(&sfd->signalfd_queue, 0, RT_WAITING_FOREVER);
            }

            rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);
            for (i = 0; i < sfd->sig_num; i++)
            {
                if (i < user_buf_num)
                {
                    memcpy(&buffer[i], &sfd->info[i], sizeof(struct signalfd_siginfo));
                    sfd->sig_num -= 1;
                    sig_num += 1;
                }
                else
                {
                    break;
                }
            }

            for (int j = 0; j < sfd->sig_num; j++)
            {
                memcpy(&sfd->info[j], &sfd->info[i++], sizeof(struct signalfd_siginfo));
            }

            rt_mutex_release(&sfd->lock);

            ret = sizeof(struct signalfd_siginfo) * sig_num;
        }
    }

    return ret;
}

/**
 * @brief   Callback function for signalfd file descriptor notifications.
 * @param   signalfd_queue  Pointer to the signalfd queue.
 * @param   signum          Signal number.
 */
static void signalfd_callback(rt_wqueue_t *signalfd_queue, int signum)
{
    struct rt_signalfd_ctx *sfd;

    sfd = rt_container_of(signalfd_queue, struct rt_signalfd_ctx, signalfd_queue);

    if (sfd)
    {
        if (sigismember(&sfd->sigmask, signum))
        {
            rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);
            if (sfd->sig_num < SIGINFO_MAX)
            {
                sfd->info[sfd->sig_num].si_signo = signum;
                sfd->sig_num += 1;
            }
            rt_mutex_release(&sfd->lock);
            rt_wqueue_wakeup(signalfd_queue, (void *)POLLIN);
        }
    }
}

/**
 * @brief   Exit hook for a process registered on a signalfd.
 * @param   signalfd_queue  Pointer to the signalfd queue.
 * @param   lwp             The exiting process.
 * @note    Runs under LWP_LOCK from lwp_signal_notify_detach() after the
 *          listener node has been unlinked. Clears the process slot and drops
 *          the reference the registration took, unless close already did.
 */
static void signalfd_detach(rt_wqueue_t *signalfd_queue, struct rt_lwp *lwp)
{
    struct rt_signalfd_ctx *sfd;
    int drop_ref = 0;

    sfd = rt_container_of(signalfd_queue, struct rt_signalfd_ctx, signalfd_queue);

    rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);
    for (int i = 0; i < SIGNALFD_SHARE_MAX; i++)
    {
        if (sfd->lwp[i] == lwp)
        {
            sfd->lwp[i] = RT_NULL;
            drop_ref = 1;
            break;
        }
    }
    rt_mutex_release(&sfd->lock);

    if (drop_ref)
    {
        lwp_ref_dec(lwp);
    }
}

/**
 * @brief   Looks up the slot of a process, or a free slot, in a signalfd context.
 * @param   sfd         Pointer to the signalfd context.
 * @param   lwp         Process to look for.
 * @param   empty_slot  Receives the first free slot index, or -1.
 * @return  1 if the process is already registered, 0 otherwise.
 * @note    Caller holds sfd->lock.
 */
static int signalfd_find_slot(struct rt_signalfd_ctx *sfd, struct rt_lwp *lwp, int *empty_slot)
{
    *empty_slot = -1;

    for (int i = 0; i < SIGNALFD_SHARE_MAX; i++)
    {
        if (sfd->lwp[i] == lwp)
        {
            return 1;
        }
        if (sfd->lwp[i] == RT_NULL && *empty_slot == -1)
        {
            *empty_slot = i;
        }
    }

    return 0;
}

/**
 * @brief   Registers the calling process on a signalfd context.
 * @param   sfd Pointer to the signalfd context.
 * @return  Upon successful completion, returns 0; otherwise, returns an error code.
 * @note    Lookup, slot assignment and listener insertion happen in one
 *          critical section under LWP_LOCK(self) -> sfd->lock, so another
 *          thread can only see the slot once the listener is installed. An
 *          existing registration is answered from that first lookup without
 *          allocating; a node is only allocated when a new registration is
 *          needed, and the lookup is repeated after the allocation.
 */
static int signalfd_add_notify(struct rt_signalfd_ctx *sfd)
{
    struct rt_lwp_notify *lwp_notify = RT_NULL;
    struct rt_lwp *curr_lwp;
    int registered;
    int empty_slot;
    int err = 0;

    if (!sfd)
    {
        return -EINVAL;
    }

    curr_lwp = lwp_self();
    if (!curr_lwp)
    {
        return -EINVAL;
    }

    for (;;)
    {
        LWP_LOCK(curr_lwp);
        rt_mutex_take(&sfd->lock, RT_WAITING_FOREVER);

        if (sfd->closing)
        {
            err = -EBADF;
            break;
        }

        registered = signalfd_find_slot(sfd, curr_lwp, &empty_slot);
        if (registered)
        {
            /* already registered: nothing to allocate or link */
            break;
        }
        if (empty_slot < 0)
        {
            err = -EMFILE;
            break;
        }
        if (lwp_notify)
        {
            /* the slot owns this reference until the release work or the exit hook clears it */
            lwp_ref_inc(curr_lwp);
            sfd->lwp[empty_slot] = curr_lwp;
            lwp_signal_notify_add(curr_lwp, lwp_notify);
            lwp_notify = RT_NULL;
            break;
        }

        /* a new registration is needed: allocate outside the locks and look again */
        rt_mutex_release(&sfd->lock);
        LWP_UNLOCK(curr_lwp);

        lwp_notify = (struct rt_lwp_notify *)rt_malloc(sizeof(struct rt_lwp_notify));
        if (!lwp_notify)
        {
            rt_set_errno(ENOMEM);
            return -ENOMEM;
        }
        lwp_notify->notify = signalfd_callback;
        lwp_notify->detach = signalfd_detach;
        lwp_notify->signalfd_queue = &sfd->signalfd_queue;
    }

    rt_mutex_release(&sfd->lock);
    LWP_UNLOCK(curr_lwp);

    if (lwp_notify)
    {
        /* the process got registered meanwhile, or the context is closing */
        rt_free(lwp_notify);
    }

    if (err < 0)
    {
        rt_set_errno(-err);
    }

    return err;
}

/**
 * @brief   Creates a new signalfd file descriptor or modifies an existing one.
 * @param   fd      File descriptor to modify (-1 to create a new one).
 * @param   mask    Signal mask.
 * @param   flags   File descriptor flags.
 * @return  Upon successful completion, returns the file descriptor number; otherwise, returns an error code.
 */
static int signalfd_do(int fd, const sigset_t *mask, int flags)
{
    struct dfs_file *df;
    struct rt_signalfd_ctx *sfd;
    rt_err_t ret = 0;

    if (fd == -1)
    {
        fd = fd_new();
        if (fd < 0)
        {
            return -1;
        }

        ret = fd;
        df = fd_get(fd);

        if (df)
        {
            sfd = (struct rt_signalfd_ctx *)rt_malloc(sizeof(struct rt_signalfd_ctx));
            if (sfd)
            {
                df->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
                if (df->vnode)
                {
                    dfs_vnode_init(df->vnode, FT_REGULAR, &signalfd_fops);
                    df->vnode->data = sfd;

                    for (int i = 0; i < SIGNALFD_SHARE_MAX; i++)
                    {
                        sfd->lwp[i] = RT_NULL;
                    }

                    sigemptyset(&sfd->sigmask);
                    memcpy(&sfd->sigmask, mask, sizeof(sigset_t));

                    sfd->sig_num = 0;
                    sfd->closing = 0;

                    rt_mutex_init(&sfd->lock, SIGNALFD_MUTEX_NAME, RT_IPC_FLAG_FIFO);
                    rt_wqueue_init(&sfd->signalfd_queue);

                    if (signalfd_add_notify(sfd) < 0)
                    {
                        /* nothing is registered yet: tear down while df is still ours */
                        rt_mutex_detach(&sfd->lock);
                        df->vnode->data = RT_NULL;
                        rt_free(df->vnode);
                        df->vnode = RT_NULL;
                        rt_free(sfd);
                        fd_release(fd);
                        return -1;
                    }

                    df->flags |= flags;

#ifdef RT_USING_DFS_V2
                    df->fops = &signalfd_fops;
#endif
                }
                else
                {
                    fd_release(fd);
                    rt_free(sfd);
                    ret = -1;
                }
            }
            else
            {
                fd_release(fd);
                ret = -1;
            }
        }
        else
        {
            fd_release(fd);
        }
    }
    else
    {
        df = fd_get(fd);
        if (df)
        {
            sfd = df->vnode->data;
            df->flags = flags;
            sigemptyset(&sfd->sigmask);
            memcpy(&sfd->sigmask, mask, sizeof(sigset_t));
            ret = fd;
        }
        else
        {
            rt_set_errno(EBADF);
            ret = -1;
        }
    }

    return ret;
}

/**
 * @brief   Creates a new signalfd file descriptor or modifies an existing one.
 * @param   fd      File descriptor to modify (-1 to create a new one).
 * @param   mask    Signal mask.
 * @param   flags   File descriptor flags.
 * @return  Upon successful completion, returns the file descriptor number; otherwise, returns an error code.
 */
int signalfd(int fd, const sigset_t *mask, int flags)
{
    return signalfd_do(fd, mask, flags);
}
