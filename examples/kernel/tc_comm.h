
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 *
 */
#ifndef __TC_COMM_H__
#define __TC_COMM_H__

/*
 * RT-Thread TestCase
 *
 */
#include <rtthread.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#if RT_THREAD_PRIORITY_MAX == 8
#define THREAD_PRIORITY        6
#elif RT_THREAD_PRIORITY_MAX == 32
#define THREAD_PRIORITY        25
#elif RT_THREAD_PRIORITY_MAX == 256
#define THREAD_PRIORITY        200
#endif
#define THREAD_STACK_SIZE    512
#define THREAD_TIMESLICE    5

#define TC_STAT_END        0x00
#define TC_STAT_RUNNING    0x01
#define TC_STAT_FAILED    0x10
#define TC_STAT_PASSED    0x00

#ifdef RT_USING_TC
void tc_start(const char* tc_prefix);
void tc_stop(void);
void tc_done(rt_uint8_t state);
void tc_stat(rt_uint8_t state);
void tc_cleanup(void (*cleanup)(void));
#else
#define tc_start(x)
#define tc_stop()
#define tc_done(s)
#define tc_stat(s)
#define tc_cleanup(c)
#endif

#endif

