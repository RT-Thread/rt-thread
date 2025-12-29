/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    CPU time APIs (delegates to clock_time core)
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/clock_time.h>

/*
 * Additional CPU time utility functions
 * Core implementations are in clock_time_tick.c
 */

/* These functions are implemented inline or use the core APIs */

/* Note: The main cputime APIs are now:
 *   rt_clock_cputimer_getres()
 *   rt_clock_cputimer_getfrq()
 *   rt_clock_cputimer_getcnt()
 *   rt_clock_cputimer_init()
 *
 * These are defined in clock_time_tick.c as weak functions
 * that can be overridden by BSP implementations.
 */
