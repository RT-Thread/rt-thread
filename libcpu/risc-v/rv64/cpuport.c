/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-26     Shell        lockless rt_completion
 */

#include <rtthread.h>

#undef rt_hw_isb
rt_weak void rt_hw_isb(void)
{
    return ;
}
