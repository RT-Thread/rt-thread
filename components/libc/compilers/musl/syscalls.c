/**
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-18     Meco Man     first version
 */

#include <rtthread.h>

/**
 * @brief   Returns a pointer to the thread-specific errno variable.
 *
 * This function returns a pointer to the thread-specific errno variable.
 * It allows accessing the errno variable for the current thread, which is
 * useful in multithreaded applications.
 *
 * @return  A pointer to the errno variable for the current thread.
 */
int *__errno_location(void)
{
    return _rt_errno();
}

/**
 * @brief   Returns a pointer to the thread-specific errno variable.
 *
 * This function is an alias for __errno_location and returns a pointer to
 * the thread-specific errno variable. It provides the same functionality.
 *
 * @return  A pointer to the errno variable for the current thread.
 */
int *___errno_location(void)
{
    return _rt_errno();
}
