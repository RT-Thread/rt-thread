/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/* sys channel */

/**
 * @brief Opens a communication channel.
 *
 * This system call is used to open a communication channel with a specified name and set of flags.
 * The channel allows for inter-process or inter-thread communication, depending on the underlying system.
 * The `name` parameter specifies the name of the channel, while the `flags` parameter allows
 * configuration of the channel's behavior (e.g., read/write permissions, blocking or non-blocking mode).
 *
 * @param[in] name   The name of the communication channel to be opened.
 * @param[in] flags  The flags to configure the behavior of the channel. These flags may
 *                   define various properties such as access mode (e.g., read-only, write-only)
 *                   or synchronization mode (e.g., blocking, non-blocking).
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The channel was successfully opened.
 *                    - Other error codes may indicate issues with the channel opening process.
 *
 * @warning Ensure that the correct flags are passed to configure the channel as required,
 *          as improper configuration might lead to access issues, data loss, or undefined behavior.
 */
sysret_t sys_channel_open(const char *name, int flags)
{
    rt_size_t ret = 0;
    char *kname = RT_NULL;
    int len = 0;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return -EFAULT;
    }

    ret = lwp_channel_open(FDT_TYPE_LWP, kname, flags);

    kmem_put(kname);

    return ret;
}

/**
 * @brief Closes an open communication channel.
 *
 * This system call is used to close an already open communication channel specified by the file descriptor `fd`.
 * After closing, the channel can no longer be used for communication, and any resources associated with
 * the channel will be released. This function is necessary for proper resource management, ensuring that
 * system resources (e.g., memory or file handles) are freed when no longer needed.
 *
 * @param[in] fd     The file descriptor of the communication channel to be closed.
 *
 * @return sysret_t  Returns a status code:
 *                    - `SYSRET_OK`: The channel was successfully closed.
 *                    - Other error codes may indicate issues with the channel closing process.
 *
 * @note This function should be called after communication is finished and the channel is no longer
 *       needed, to release any system resources associated with it.
 *
 * @warning Calling this function on an invalid or already closed file descriptor may lead to
 *          undefined behavior or errors. Ensure that the file descriptor is valid and that the
 *          channel is not already closed before attempting to close it.
 */
sysret_t sys_channel_close(int fd)
{
    return lwp_channel_close(FDT_TYPE_LWP, fd);
}

/**
 * @brief Sends a message through a communication channel.
 *
 * This system call is used to send a message through a specified communication channel identified
 * by the file descriptor `fd`. The message to be sent is provided in the `data` parameter.
 * It allows inter-process or inter-thread communication by transmitting the given message over
 * the open channel.
 *
 * @param[in] fd     The file descriptor of the communication channel to send the message to.
 * @param[in] data   The message data to be sent. This parameter is typically a structure
 *                   containing the message content and metadata.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The message was successfully sent.
 *                    - Other error codes may indicate issues with the message sending process.
 *
 * @note Ensure the channel is open and properly configured for sending messages before
 *       calling this function. Additionally, confirm that the `data` structure is valid and
 *       initialized with the appropriate content.
 *
 * @warning Failure to verify the channel's readiness or the validity of the data may lead
 *          to errors, data loss, or undefined behavior.
 */
sysret_t sys_channel_send(int fd, rt_channel_msg_t data)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;

    if (!lwp_user_accessable((void *)data, sizeof(*data)))
    {
        return -EFAULT;
    }

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kdata, data, sizeof(*kdata)) != sizeof(*kdata))
    {
        kmem_put(kdata);
        return -EFAULT;
    }

    ret = lwp_channel_send(FDT_TYPE_LWP, fd, kdata);

    kmem_put(kdata);

    return ret;
}

/**
 * @brief Sends a message through a communication channel and waits for a response with a timeout.
 *
 * This system call sends a message (`data`) through a specified communication channel identified by the file descriptor `fd`.
 * It then waits for a response (`data_ret`) within the specified timeout period. This is a synchronous operation
 * commonly used in request-response communication patterns between processes or threads.
 *
 * @param[in]  fd        The file descriptor of the communication channel to send the message to.
 * @param[in]  data      The message data to be sent. This is typically a structure containing
 *                       the message content and metadata.
 * @param[out] data_ret  The buffer to store the response message received from the channel.
 * @param[in]  time      The timeout period (in milliseconds) to wait for the response.
 *                       If set to a negative value, the function will wait indefinitely.
 *
 * @return sysret_t      Returns a status code:
 *                        - `0`: The message was successfully sent, and a response was received.
 *                        - Other error codes may indicate issues with the communication process.
 *
 * @note This function combines sending and receiving operations into a single atomic action.
 *       It is useful for scenarios requiring synchronous communication with a defined timeout
 *       to handle cases where a response may not be immediately available.
 *
 * @warning Ensure that the channel is open and properly configured for bidirectional communication.
 *          Verify that the `data` structure is valid and initialized, and the `data_ret` buffer is large
 *          enough to store the expected response to avoid memory issues or data corruption.
 */
sysret_t sys_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;
    rt_channel_msg_t kdata_ret = RT_NULL;

    if (!lwp_user_accessable((void *)data, sizeof(*data)))
    {
        return -EFAULT;
    }

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kdata, data, sizeof(*kdata)) != sizeof(*kdata))
    {
        kmem_put(kdata);
        return -EFAULT;
    }

    kdata_ret = kmem_get(sizeof(*data_ret));
    if (kdata_ret == RT_NULL)
    {
        return -ENOMEM;
    }

    ret = lwp_channel_send_recv_timeout(FDT_TYPE_LWP, fd, kdata, kdata_ret, time);

    lwp_put_to_user(data_ret, kdata_ret, sizeof(*kdata_ret));
    kmem_put(kdata);
    kmem_put(kdata_ret);

    return ret;
}

/**
 * @brief Sends a reply message through a communication channel.
 *
 * This system call is used to send a reply (`data`) through a communication channel identified
 * by the file descriptor `fd`. It is typically called in response to a received request
 * within a request-response communication pattern. The reply is sent to the requesting entity
 * through the same channel.
 *
 * @param[in] fd     The file descriptor of the communication channel to send the reply to.
 * @param[in] data   The reply message to be sent. This is typically a structure containing
 *                   the reply content and metadata.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The reply was successfully sent.
 *                    - Other error codes may indicate issues with the reply sending process.
 *
 * @note This function is usually called in a server or responder context, where a request
 *       is received, processed, and the result is sent back to the requester. Ensure that
 *       the channel is open and configured to send replies before calling this function.
 *
 * @warning Ensure the `data` structure is valid and properly initialized before sending.
 *          Sending invalid or corrupted data may lead to unexpected behavior or communication failures.
 */
sysret_t sys_channel_reply(int fd, rt_channel_msg_t data)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;

    if (!lwp_user_accessable((void *)data, sizeof(*data)))
    {
        return -EFAULT;
    }

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kdata, data, sizeof(*kdata)) != sizeof(*data))
    {
        kmem_put(kdata);
        return -EFAULT;
    }

    ret = lwp_channel_reply(FDT_TYPE_LWP, fd, kdata);

    kmem_put(kdata);

    return ret;
}

/**
 * @brief Receives a message from a communication channel with a timeout.
 *
 * This system call attempts to receive a message from a specified communication channel identified
 * by the file descriptor `fd`. The received message is stored in the `data` buffer. If no message
 * is available within the specified timeout period, the function returns with a timeout status.
 *
 * @param[in]  fd     The file descriptor of the communication channel to receive the message from.
 * @param[out] data   The buffer to store the received message. This parameter is typically a
 *                    structure containing the message content and metadata.
 * @param[in]  time   The timeout period (in milliseconds) to wait for a message.
 *                    A negative value indicates that the function will wait indefinitely.
 *
 * @return sysret_t   Returns a status code:
 *                     - `0`: A message was successfully received.
 *                     - `-ETIMEDOUT`: The operation timed out before a message was received.
 *                     - Other error codes may indicate issues with the message receiving process.
 *
 * @note This function is useful in scenarios where blocking indefinitely is not desirable,
 *       allowing the caller to specify a timeout for receiving messages. It is commonly
 *       used in event-driven or time-sensitive communication systems.
 *
 * @warning Ensure that the channel is open and configured for receiving messages before calling
 *          this function. The `data` buffer must be valid and large enough to store the expected
 *          message to avoid memory corruption or data loss.
 */
sysret_t sys_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time)
{
    rt_size_t ret = 0;
    rt_channel_msg_t kdata = RT_NULL;

    kdata = kmem_get(sizeof(*data));
    if (kdata == RT_NULL)
    {
        return -ENOMEM;
    }

    ret = lwp_channel_recv_timeout(FDT_TYPE_LWP, fd, kdata, time);

    lwp_put_to_user(data, kdata, sizeof(*kdata));
    kmem_put(kdata);

    return ret;
}

static struct rt_semaphore critical_lock;

static int critical_init(void)
{
    rt_sem_init(&critical_lock, "ct_lock", 1, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_DEVICE_EXPORT(critical_init);

/**
 * @brief Enters a critical section to prevent context switching or interrupts.
 *
 * @note Critical sections are typically used to protect shared resources or perform
 *       non-interruptible operations. Ensure to exit the critical section as soon as
 *       possible by calling `sys_exit_critical` to avoid system performance degradation
 *       or deadlocks.
 *
 * @warning Failure to exit a critical section (e.g., due to an exception or missing
 *          `sys_exit_critical` call) may lead to system instability or a complete halt.
 */
void sys_enter_critical(void)
{
    rt_sem_take(&critical_lock, RT_WAITING_FOREVER);
}

/**
 * @brief Exits a critical section and restores the system's previous state.
 *
 * @note Exiting the critical section as soon as the protected operation is completed
 *       is essential to avoid performance degradation or system deadlocks. Ensure
 *       that every call to `sys_enter_critical` is matched with a corresponding
 *       `sys_exit_critical` call.
 *
 * @warning Calling this function without a prior `sys_enter_critical` may result
 *          in undefined behavior or system instability. Use carefully in nested
 *          critical sections and ensure proper tracking of critical section depth
 *          if required.
 */
void sys_exit_critical(void)
{
    rt_sem_release(&critical_lock);
}

int __sys_log_enable = 0;

/**
 * @brief Implements the shell command used to toggle syscall logging.
 *
 * @param[in] argc The number of command arguments.
 * @param[in] argv The command argument vector.
 * @return int Zero on success, otherwise a command error.
 */
static int sys_log_enable(int argc, char **argv)
{
    if (argc == 1)
    {
        rt_kprintf("sys_log = %d\n", __sys_log_enable);
        return 0;
    }
    else
    {
        __sys_log_enable = atoi(argv[1]);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(sys_log_enable, sys_log, sys_log 1(enable) / 0(disable));

/**
 * @brief Logs a message to the system logging mechanism.
 *
 * This system call writes a log message to the system log for diagnostic or informational purposes.
 * The message is specified by the `log` parameter, and its size is given by the `size` parameter.
 * The logging mechanism is typically used for tracking system events, debugging, or reporting errors.
 *
 * @param[in] log   A pointer to the message to be logged. The message should be a valid character
 *                  array or string.
 * @param[in] size  The size of the log message in bytes. This specifies the number of bytes to write
 *                  from the `log` buffer.
 *
 * @return sysret_t Returns a status code:
 *                   - `0`: The log message was successfully written.
 *                   - Other error codes may indicate issues with the logging process.
 *
 * @note Ensure that the `log` pointer is valid and points to a properly initialized memory buffer.
 *       Truncation may occur if the logging system has a size limitation. Logging should not be used
 *       in performance-critical paths as it may introduce latency.
 *
 * @warning Passing a `NULL` pointer or an invalid `size` may lead to undefined behavior. Ensure the
 *          logging system is properly initialized before invoking this function.
 */
sysret_t sys_log(const char *log, int size)
{
    char *klog = RT_NULL;
    rt_device_t console = RT_NULL;

    if (!lwp_user_accessable((void *)log, size))
    {
        return -EFAULT;
    }

    klog = kmem_get(size);
    if (klog == RT_NULL)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user((void *)klog, (void *)log, size) != size)
    {
        kmem_put(klog);
        return -EINVAL;
    }

    console = rt_console_get_device();

    if (console && __sys_log_enable)
    {
        rt_device_write(console, -1, klog, size);
    }

    kmem_put(klog);

    return 0;
}
