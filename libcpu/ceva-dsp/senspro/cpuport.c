/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-13     Eran         the first version.
 */

#include <rtthread.h>

volatile rt_uint32_t rt_interrupt_from_thread = 0;
volatile rt_uint32_t rt_interrupt_to_thread   = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;
