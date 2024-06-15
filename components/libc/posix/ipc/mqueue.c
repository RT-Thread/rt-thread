/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2023-07-20       zmq810150896    first version
 * 2024-04-30       TroyMitchell    Add comments for all functions
 */

#include <dfs_file.h>
#include <unistd.h>
#include "mqueue.h"

/**
 * @brief   Sets the attributes of a message queue.
 * @param   id Identifier of the message queue.
 * @param   mqstat Pointer to a struct mq_attr containing the new attributes (ignored).
 * @param   omqstat Pointer to a struct mq_attr where the old attributes will be stored.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function sets the attributes of the message queue specified by id.
 *          The new attributes are provided in the mqstat parameter, but this implementation ignores it.
 *          Instead, the function calls mq_getattr() to retrieve the current attributes of the message queue
 *          and stores them in the struct mq_attr pointed to by omqstat.
 *          If mqstat is RT_NULL, the function behaves as a query and retrieves the attributes without setting new values.
 *          If an error occurs during the operation, errno is set to indicate the error, and the function returns -1.
 */
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

/**
 * @brief   Gets the attributes of a message queue.
 * @param   id Identifier of the message queue.
 * @param   mqstat Pointer to a struct mq_attr where the attributes will be stored.
 * @return  Upon successful completion, returns 0; otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function retrieves the attributes of the message queue specified by id.
 *          The attributes include the maximum number of messages that can be queued (mq_maxmsg),
 *          the maximum size of each message (mq_msgsize), the number of messages currently in the queue (mq_curmsgs),
 *          and the flags associated with the queue (mq_flags).
 *          The attributes are stored in the struct mq_attr pointed to by mqstat.
 *          If the message queue identified by id does not exist or if mqstat is a null pointer, errno is set to EBADF,
 *          indicating a bad file descriptor, and the function returns -1.
 *          Otherwise, the function retrieves the attributes from the message queue and stores them in mqstat, returning 0 to indicate success.
 */
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

/**
 * @brief   Opens or creates a message queue.
 * @param   name Name of the message queue.
 * @param   oflag Flags indicating the access mode and creation options (O_CREAT, O_EXCL, etc.).
 * @param   ... Additional arguments for creation options (mode, attr) (ignored).
 * @return  Upon successful completion, returns a message queue descriptor (mqd_t);
 *          otherwise, returns (mqd_t)(-1) and sets errno to indicate the error.
 *
 * @note    This function opens or creates a message queue specified by name with the specified flags.
 *          If the name starts with '/', the leading '/' is ignored.
 *          The function then checks the length of the name and verifies if it exceeds the maximum allowed length.
 *          If the name is too long, errno is set to ENAMETOOLONG, indicating a name too long error.
 *          Next, the function attempts to find the message queue file corresponding to the name.
 *          If the file exists and O_CREAT and O_EXCL flags are both set, indicating exclusive creation,
 *          errno is set to EEXIST, indicating that the file already exists.
 *          If the file does not exist and O_CREAT flag is set, the function checks the message queue attributes.
 *          If the maximum number of messages (mq_maxmsg) in the attributes is less than or equal to 0,
 *          errno is set to EINVAL, indicating an invalid argument for the maximum number of messages.
 *          If the file does not exist and O_CREAT flag is not set, errno is set to ENOENT, indicating no such file or directory.
 *          If the message queue needs to be created (O_CREAT flag set), a new mqueue_file structure is allocated and initialized
 *          with the specified message queue attributes, and it is inserted into the message queue filesystem.
 *          Finally, the function constructs the path to the message queue device file, opens it with the specified flags,
 *          and returns the file descriptor as a message queue descriptor (mqd_t).
 */
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

/**
 * @brief   Receives a message from a message queue.
 * @param   id Message queue descriptor.
 * @param   msg_ptr Pointer to the buffer where the received message will be stored.
 * @param   msg_len Maximum size of the message buffer.
 * @param   msg_prio Pointer to an unsigned integer where the priority of the received message will be stored (ignored).
 * @return  Upon successful completion, returns the number of bytes received;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function receives a message from the message queue identified by id.
 *          The received message is stored in the buffer pointed to by msg_ptr, with a maximum size of msg_len bytes.
 *          The priority of the received message is stored in the unsigned integer pointed to by msg_prio (ignored in this implementation).
 *          If either the message queue identified by id or the msg_ptr buffer is a null pointer, errno is set to EINVAL,
 *          indicating an invalid argument, and the function returns -1.
 *          The function then attempts to receive a message from the message queue using the rt_mq_recv_prio() function
 *          with an infinite timeout and uninterruptible mode.
 *          If a message is successfully received, the function returns the number of bytes received.
 *          If an error occurs during the receive operation, errno is set to EBADF, indicating a bad file descriptor,
 *          and the function returns -1.
 */
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
        return result;

    rt_set_errno(EBADF);
    return -1;
}
RTM_EXPORT(mq_receive);

/**
 * @brief   Sends a message to a message queue.
 * @param   id Message queue descriptor.
 * @param   msg_ptr Pointer to the buffer containing the message to be sent.
 * @param   msg_len Size of the message to be sent.
 * @param   msg_prio Priority of the message to be sent.
 * @return  Upon successful completion, returns 0;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function sends a message to the message queue identified by id.
 *          The message to be sent is contained in the buffer pointed to by msg_ptr, with a size of msg_len bytes.
 *          The priority of the message is specified by the msg_prio parameter.
 *          If either the message queue identified by id or the msg_ptr buffer is a null pointer, errno is set to EINVAL,
 *          indicating an invalid argument, and the function returns -1.
 *          The function then attempts to send the message to the message queue using the rt_mq_send_wait_prio() function
 *          with zero timeout and uninterruptible mode.
 *          If the message is successfully sent, the function returns 0.
 *          If an error occurs during the send operation, errno is set to EBADF, indicating a bad file descriptor,
 *          and the function returns -1.
 */
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

/**
 * @brief   Receives a message from a message queue with a timeout.
 * @param   id Message queue descriptor.
 * @param   msg_ptr Pointer to the buffer where the received message will be stored.
 * @param   msg_len Maximum size of the message buffer.
 * @param   msg_prio Pointer to an unsigned integer where the priority of the received message will be stored.
 * @param   abs_timeout Pointer to a struct timespec specifying the absolute timeout value (ignored if null).
 * @return  Upon successful completion, returns the number of bytes received;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function receives a message from the message queue identified by id with a specified timeout.
 *          The received message is stored in the buffer pointed to by msg_ptr, with a maximum size of msg_len bytes.
 *          The priority of the received message is stored in the unsigned integer pointed to by msg_prio.
 *          If either the message queue identified by id or the msg_ptr buffer is a null pointer, errno is set to EINVAL,
 *          indicating an invalid argument, and the function returns -1.
 *          The function then converts the absolute timeout value specified by abs_timeout to system ticks,
 *          or sets the timeout to RT_WAITING_FOREVER if abs_timeout is null.
 *          It attempts to receive a message from the message queue using the rt_mq_recv_prio() function
 *          with the specified timeout and uninterruptible mode.
 *          If a message is successfully received, the function returns the number of bytes received.
 *          If the receive operation times out, errno is set to ETIMEDOUT, indicating a timeout error.
 *          If the received message is too large for the specified buffer, errno is set to EMSGSIZE, indicating a message too large error.
 *          If an unknown error occurs during the receive operation, errno is set to EBADMSG, indicating a bad message error,
 *          and the function returns -1.
 */
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
        return result;

    if (result == -RT_ETIMEOUT)
        rt_set_errno(ETIMEDOUT);
    else if (result == -RT_ERROR)
        rt_set_errno(EMSGSIZE);
    else
        rt_set_errno(EBADMSG);

    return -1;
}
RTM_EXPORT(mq_timedreceive);

/**
 * @brief   Sends a message to a message queue with a timeout (not supported).
 * @param   id Message queue descriptor.
 * @param   msg_ptr Pointer to the buffer containing the message to be sent.
 * @param   msg_len Size of the message to be sent.
 * @param   msg_prio Priority of the message to be sent.
 * @param   abs_timeout Pointer to a struct timespec specifying the absolute timeout value (ignored).
 * @return  Upon successful completion, returns 0;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function attempts to send a message to the message queue identified by id with a specified timeout,
 *          but timed send is not supported in the RT-Thread environment.
 *          Therefore, the function simply delegates the message sending operation to the mq_send() function,
 *          which does not involve a timeout.
 *          The abs_timeout parameter is ignored, and the message is sent without waiting for a timeout to occur.
 *          The function returns the result of the mq_send() function, which indicates whether the message was successfully sent.
 */
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

/**
 * @brief   Registers for notification when a message is available in a message queue (not supported).
 * @param   id Message queue descriptor.
 * @param   notification Pointer to a struct sigevent specifying the notification settings (ignored).
 * @return  Upon successful completion, returns 0;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function attempts to register for notification when a message is available in the message queue identified by id.
 *          However, message queue notification is not supported in the RT-Thread environment.
 *          Therefore, this function simply sets errno to EBADF, indicating a bad file descriptor,
 *          and returns -1 to indicate that the operation is not supported.
 */
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

/**
 * @brief   Closes a message queue descriptor.
 * @param   id Message queue descriptor to be closed.
 * @return  Upon successful completion, returns 0;
 *          otherwise, returns -1 and sets errno to indicate the error.
 *
 * @note    This function closes the message queue descriptor specified by id.
 *          It delegates the closing operation to the close() function, which closes the file descriptor associated with the message queue.
 *          If the close operation is successful, the function returns 0.
 *          If an error occurs during the close operation, errno is set to indicate the error, and the function returns -1.
 */
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
