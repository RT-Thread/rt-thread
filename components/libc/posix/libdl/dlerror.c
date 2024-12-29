/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author      Notes
 * 2010-11-17     yi.qiu      first version
 */

#include <rtthread.h>
#include <rtm.h>

/**
 * @brief  retrieve a string describing the last error that occurred from a dynamic linking operation.
 *
 * @return const char* a string containing an error message describing the last error.
 *
 * @note   This function is an API of POSIX standard, which is still remaining TBD.
 */
const char *dlerror(void)
{
    return "TODO";
}
RTM_EXPORT(dlerror)
