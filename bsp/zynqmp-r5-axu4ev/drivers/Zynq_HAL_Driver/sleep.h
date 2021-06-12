/*
 * Copyright (c) 2020-2021, WangHuachen
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-30     WangHuachen  the first version
 */
#ifndef XLI_SLEEP_H
#define XLI_SLEEP_H

#include <rtthread.h>
#include <rthw.h>

#include "xil_types.h"
#include "xil_io.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void usleep(unsigned long useconds)
{
    rt_uint32_t milliseconds = useconds/1000;
    useconds = useconds%1000;
    if (milliseconds) rt_thread_mdelay(milliseconds);
    if (useconds) rt_hw_us_delay(useconds);
}

static inline void sleep(unsigned int seconds)
{
    rt_thread_delay(seconds*RT_TICK_PER_SECOND);
}

#ifdef __cplusplus
}
#endif

#endif
