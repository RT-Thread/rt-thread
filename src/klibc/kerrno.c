/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-22     Meco Man     the first version
 */

#include <rtthread.h>

/**
 * @brief A global variable used to store the error code.
 *
 * This volatile static integer is used to store the most recent error code globally.
 * Its volatile nature ensures that every read operation fetches the most current value,
 * providing real-time error status across different parts of the program.
 */
static volatile int __rt_errno;

/**
 * @struct _errno_str_t
 * @brief Structure for mapping error codes to corresponding error strings.
 *
 * This structure is used to create a mapping that associates an rt_err_t type error code
 * with a corresponding error description string.
 */
struct _errno_str_t
{
    rt_err_t error;      /**< Error code of type rt_err_t, representing different kinds of errors. */
    const char *str;     /**< Pointer to the error description string. */
};

/**
 * @brief An array containing mappings of error codes to their corresponding error strings.
 *
 * This array uses the _errno_str_t structure to define several error codes and their
 * corresponding error description strings. These mappings can be used at runtime
 * to provide more readable error information.
 */
static struct _errno_str_t  rt_errno_strs[] =
{
    {RT_EOK     , "OK     "},  /**< Operation successful. */
    {RT_ERROR   , "ERROR  "},  /**< General error. */
    {RT_ETIMEOUT, "ETIMOUT"},  /**< Operation timed out. */
    {RT_EFULL   , "ERSFULL"},  /**< Resource is full. */
    {RT_EEMPTY  , "ERSEPTY"},  /**< Resource is empty. */
    {RT_ENOMEM  , "ENOMEM "},  /**< Not enough memory. */
    {RT_ENOSYS  , "ENOSYS "},  /**< Function not implemented. */
    {RT_EBUSY   , "EBUSY  "},  /**< Resource is busy. */
    {RT_EIO     , "EIO    "},  /**< Input/output error. */
    {RT_EINTR   , "EINTRPT"},  /**< Interrupted system call. */
    {RT_EINVAL  , "EINVAL "},  /**< Invalid argument. */
    {RT_ENOENT  , "ENOENT "},  /**< No such file or directory. */
    {RT_ENOSPC  , "ENOSPC "},  /**< No space left on device. */
    {RT_EPERM   , "EPERM  "},  /**< Operation not permitted. */
    {RT_ETRAP   , "ETRAP  "},  /**< Trap error. */
};

/**
 * @brief This function return a pointer to a string that contains the
 * message of error.
 *
 * @param error the errorno code
 * @return a point to error message string
 */
const char *rt_strerror(rt_err_t error)
{
    int i = 0;

    if (error < 0)
        error = -error;

    for (i = 0; i < sizeof(rt_errno_strs) / sizeof(rt_errno_strs[0]); i++)
    {
        if (rt_errno_strs[i].error == error)
            return rt_errno_strs[i].str;
    }

    return "EUNKNOW";
}
RTM_EXPORT(rt_strerror);

/**
 * @brief This function gets the global errno for the current thread.
 *
 * @return errno
 */
rt_err_t rt_get_errno(void)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        return __rt_errno;
    }

    tid = rt_thread_self();
    if (tid == RT_NULL)
    {
        return __rt_errno;
    }

    return tid->error;
}
RTM_EXPORT(rt_get_errno);

/**
 * @brief This function sets the global errno for the current thread.
 *
 * @param error is the errno shall be set.
 */
void rt_set_errno(rt_err_t error)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        __rt_errno = error;

        return;
    }

    tid = rt_thread_self();
    if (tid == RT_NULL)
    {
        __rt_errno = error;

        return;
    }

    tid->error = error;
}
RTM_EXPORT(rt_set_errno);

/**
 * @brief This function returns the address of the current thread errno.
 *
 * @return The errno address.
 */
int *_rt_errno(void)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        return (int *)&__rt_errno;
    }

    tid = rt_thread_self();
    if (tid != RT_NULL)
    {
        return (int *) & (tid->error);
    }

    return (int *)&__rt_errno;
}
RTM_EXPORT(_rt_errno);
