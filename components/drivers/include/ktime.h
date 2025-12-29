/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Compatibility layer for legacy ktime API
 *
 * COMPATIBILITY HEADER:
 * This header provides backward compatibility for code using the old ktime API.
 * All rt_ktime_* APIs are now redirected to rt_clock_* APIs.
 *
 * The old ktime subsystem has been removed and replaced with the unified
 * clock_time subsystem. Include <drivers/clock_time.h> for new code.
 */

#ifndef __KTIME_H__
#define __KTIME_H__

#ifdef RT_USING_CLOCK_TIME
/* Include the unified clock_time header which provides all APIs */
#include <drivers/clock_time.h>

/* All rt_ktime_* APIs are already defined as macros in clock_time.h */

#else
#error "ktime subsystem has been removed. Please enable RT_USING_CLOCK_TIME in menuconfig."
#endif /* RT_USING_CLOCK_TIME */

#endif /* __KTIME_H__ */
