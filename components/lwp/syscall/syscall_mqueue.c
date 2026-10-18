/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Open a message queue.
 *
 * This function opens a message queue for communication between processes.
 * It can create a new message queue or open an existing one, depending on the specified
 * flags.
 *
 * @param[in] name  The name of the message queue. The name should be a null-terminated
 *                  string and is subject to system-specific naming conventions.
 * @param[in] flags Flags that control the behavior of the message queue. Common flags include:
 *                  - `O_CREAT`: Create the message queue if it does not exist.
 *                  - `O_EXCL`: Fail if the message queue already exists.
 *                  - `O_RDONLY`: Open the queue for reading.
 *                  - `O_WRONLY`: Open the queue for writing.
 *                  - `O_RDWR`: Open the queue for both reading and writing.
 * @param[in] mode  The mode to be applied when creating the message queue, which defines
 *                  the permissions for the message queue (e.g., read, write).
 * @param[in] attr  A pointer to a `struct mq_attr` that defines the attributes of the
 *                  message queue, such as the maximum number of messages and the size of
 *                  each message. If `NULL`, default values are used.
 *
 * @return mqd_t Returns a non-negative file descriptor for the message queue on success.
 *               On failure, returns `-1` and sets `errno` to indicate the error.
 *
 * @note If the message queue is created, its attributes (such as the maximum number of
 *       messages and message size) must be defined in the `mq_attr` structure. If the
 *       `O_CREAT` flag is not specified and the queue does not exist, the function will
 *       return `-1`.
 */
mqd_t sys_mq_open(const char *name, int flags, mode_t mode, struct mq_attr *attr)
{
    mqd_t mqdes;
    sysret_t ret = 0;
#ifdef ARCH_MM_MMU
    char *kname = RT_NULL;
    rt_size_t len = 0;
    struct mq_attr attr_k;

    len = lwp_user_strlen(name);
    if (!len)
    {
        return (mqd_t)-EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return (mqd_t)-ENOMEM;
    }

    if (attr == NULL)
    {
        attr_k.mq_maxmsg = 10;
        attr_k.mq_msgsize = 8192;
        attr_k.mq_flags = 0;
        attr = &attr_k;
    }
    else
    {
        if (!lwp_get_from_user(&attr_k, (void *)attr, sizeof(struct mq_attr)))
        {
            return -EINVAL;
        }
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    mqdes = mq_open(kname, flags, mode, &attr_k);
    if (mqdes == -1)
    {
        ret = GET_ERRNO();
    }
    lwp_put_to_user(attr, &attr_k, sizeof(struct mq_attr));
    kmem_put(kname);
#else
    mqdes = mq_open(name, flags, mode, attr);
#endif
    if (mqdes == -1)
    {
        return (mqd_t)ret;
    }
    else
    {
        return mqdes;
    }
}

/**
 * @brief Remove a message queue.
 *
 * This function removes a message queue identified by its name. If the message queue
 * is open by any process, it will be removed only when all the processes close their
 * file descriptors associated with the message queue.
 *
 * @param[in] name The name of the message queue to be removed. It should be a null-terminated
 *                 string that conforms to system-specific naming conventions.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative
 *                  error code.
 *
 * @note After a successful call, the message queue is removed from the system. However,
 *       the removal will not take effect until all processes close their file descriptors
 *       associated with the queue. The function will fail if the message queue is still
 *       open by other processes.
 */
sysret_t sys_mq_unlink(const char *name)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *kname = RT_NULL;
    rt_size_t len = 0;

    len = lwp_user_strlen(name);
    if (!len)
    {
        return -EINVAL;
    }
    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = mq_unlink(kname);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }
    kmem_put(kname);
    return ret;
#else
    ret = mq_unlink(name);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Send a message to a message queue with a timeout.
 *
 * This function sends a message to the specified message queue, but it allows the sender
 * to specify a timeout. If the message queue is full, the function will block until either
 * space becomes available or the specified timeout expires. If the timeout expires without
 * space being available, the function returns an error.
 *
 * @param[in] mqd   The message queue descriptor returned by `sys_mq_open`.
 * @param[in] msg   A pointer to the message to be sent.
 * @param[in] len   The length of the message to send.
 * @param[in] prio  The priority of the message (higher values indicate higher priority).
 * @param[in] at    A pointer to a `timespec` structure that specifies the absolute timeout.
 *                  If the timeout expires before the message can be sent, the function returns
 *                  an error.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error
 *                  code.
 *
 * @note The function uses the `timespec` structure to specify the absolute timeout. The
 *       `at` parameter should indicate the time at which the operation should time out.
 *       If the timeout is `NULL`, the function will not apply any timeout (it will block
 *       indefinitely until the message is sent).
 *
 * @see sys_mq_send
 */
sysret_t sys_mq_timedsend(mqd_t mqd, const char *msg, size_t len, unsigned prio, const struct timespec *at)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *kmsg = RT_NULL;
    struct timespec at_k;

    kmsg = (char *)kmem_get(len + 1);
    if (!kmsg)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(&at_k, (void *)at, sizeof(struct timespec));
    lwp_get_from_user(kmsg, (void *)msg, len + 1);
    ret = mq_timedsend(mqd, kmsg, len, prio, &at_k);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmsg);

    return ret;
#else
    ret = mq_timedsend(mqd, msg, len, prio, at);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Receive a message from a message queue with a timeout.
 *
 * This function attempts to receive a message from the specified message queue, but it
 * allows the receiver to specify a timeout. If the queue is empty, the function will block
 * until either a message becomes available or the specified timeout expires. If the timeout
 * expires without receiving a message, the function returns an error.
 *
 * @param[in] mqd    The message queue descriptor returned by `sys_mq_open`.
 * @param[out] msg   A pointer to the buffer where the received message will be stored.
 * @param[in] len    The maximum length of the buffer to store the received message.
 * @param[out] prio  A pointer to an unsigned integer that will be set to the priority
 *                   of the received message.
 * @param[in] at     A pointer to a `timespec` structure that specifies the absolute timeout.
 *                   If the timeout expires before a message is received, the function will
 *                   return an error.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The function uses the `timespec` structure to specify the absolute timeout. The
 *       `at` parameter should indicate the time at which the operation should time out.
 *       If the timeout is `NULL`, the function will block indefinitely until a message is
 *       received.
 *
 * @see sys_mq_receive
 */
sysret_t sys_mq_timedreceive(mqd_t mqd, char * restrict msg, size_t len, unsigned * restrict prio, const struct timespec * restrict at)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char * restrict kmsg = RT_NULL;

    struct timespec at_k;

    kmsg = (char * restrict)kmem_get(len + 1);
    if (!kmsg)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kmsg, (void *)msg, len + 1);
    if (at == RT_NULL)
    {
        ret = mq_timedreceive(mqd, kmsg, len, prio, RT_NULL);
    }
    else
    {
        if (!lwp_get_from_user(&at_k, (void *)at, sizeof(struct timespec)))
        {
            return -EINVAL;
        }
        ret = mq_timedreceive(mqd, kmsg, len, prio, &at_k);
    }

    if (ret > 0)
    {
        lwp_put_to_user(msg, kmsg, len + 1);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmsg);

    return ret;
#else
    ret = mq_timedreceive(mqd, msg, len, prio, at);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Set up asynchronous notification for a message queue.
 *
 * This function configures asynchronous notification for a message queue. When a message
 * is available in the queue, the system can notify the calling process through a signal
 * or another method specified in the `sigevent` structure. This is typically used to allow
 * a process to be notified when a message arrives without having to block in the receive call.
 *
 * @param[in] mqd  The message queue descriptor returned by `sys_mq_open`.
 * @param[in] sev  A pointer to a `sigevent` structure that specifies the notification
 *                 mechanism to be used when a message is received. It could include
 *                 signals or other notification types such as event flags or message passing.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function enables asynchronous notification, but the specific behavior depends
 *       on the configuration specified in the `sev` parameter, which could involve signals
 *       or other forms of notification.
 *
 * @see sys_mq_send, sys_mq_timedreceive
 */
sysret_t sys_mq_notify(mqd_t mqd, const struct sigevent *sev)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct sigevent sev_k;
    lwp_get_from_user(&sev_k, (void *)sev, sizeof(struct timespec));
    ret = mq_notify(mqd, &sev_k);
#else
    ret = mq_notify(mqd, sev);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/**
 * @brief Get or set attributes of a message queue.
 *
 * This function allows you to get or set the attributes of an existing message queue.
 * If the `new` attribute structure is non-NULL, it updates the message queue with the new
 * attributes. Otherwise, If the `old` attribute structure is non-NULL, it will return the current
 * attributes of the message queue.
 *
 * @param[in] mqd  The message queue descriptor returned by `sys_mq_open`.
 * @param[in] new  A pointer to a `mq_attr` structure containing the new attributes to set.
 *                 If `NULL`, the function will not modify the message queue attributes.
 * @param[out] old A pointer to a `mq_attr` structure where the current message queue
 *                 attributes will be returned. If `NULL`, the current attributes will not
 *                 be returned.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @note The `mq_attr` structure contains parameters like the maximum number of messages,
 *       the maximum message size, and other attributes that control the behavior of the
 *       message queue.
 *
 * @see sys_mq_open, sys_mq_notify
 */
sysret_t sys_mq_getsetattr(mqd_t mqd, const struct mq_attr * restrict new, struct mq_attr * restrict old)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct mq_attr);
    struct mq_attr * restrict knew = NULL;
    struct mq_attr * restrict kold = NULL;

    if (new != RT_NULL)
    {
        if (!lwp_user_accessable((void *)new, size))
        {
            return -EFAULT;
        }
        knew = kmem_get(size);
        if (!knew)
        {
            return -ENOMEM;
        }
        lwp_get_from_user(knew, (void *)new, size);
    }

    if (!lwp_user_accessable((void *)old, size))
    {
        return -EFAULT;
    }
    kold = kmem_get(size);
    if (!kold)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kold, (void *)old, size);
    ret = mq_setattr(mqd, knew, kold);
    if (ret != -1)
    {
        lwp_put_to_user(old, kold, size);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kold);
    if (new != RT_NULL)
    {
        kmem_put(knew);
    }

    return ret;
#else
    ret = mq_setattr(mqd, new, old);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/**
 * @brief Close a message queue descriptor.
 *
 * This function closes a message queue descriptor. After calling this function, the
 * descriptor can no longer be used to interact with the message queue. Any resources
 * associated with the descriptor are released. If the message queue was opened with the
 * `O_CLOEXEC` flag, it will be automatically closed when the calling process executes
 * an `exec` system call.
 *
 * @param[in] mqd  The message queue descriptor to be closed. It was previously returned
 *                 by `sys_mq_open`.
 *
 * @return sysret_t Returns `0` on success. On failure, returns a negative error code.
 *
 * @see sys_mq_open, sys_mq_unlink
 */
sysret_t sys_mq_close(mqd_t mqd)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    ret = mq_close(mqd);
#else
    ret = mq_close(mqd);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}
