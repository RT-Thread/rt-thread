/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-18     Meco Man     first version
 */

#include <rtthread.h>

int *__errno_location(void)
{
    return _rt_errno();
}
int *___errno_location(void)
{
    return _rt_errno();
}
