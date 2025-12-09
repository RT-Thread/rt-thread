/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Stub header for cputime compatibility
 */

#ifndef __DRIVERS_CPUTIME_H__
#define __DRIVERS_CPUTIME_H__

/*
 * This is a compatibility stub header.
 * The cputime subsystem has been replaced by the unified clock_time subsystem.
 * Please update your code to use <drivers/clock_time.h> instead.
 */

#include <drivers/clock_time.h>

#warning "drivers/cputime.h is deprecated. Please use drivers/clock_time.h instead."

#endif /* __DRIVERS_CPUTIME_H__ */
