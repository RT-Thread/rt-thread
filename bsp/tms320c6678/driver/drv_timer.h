/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#ifndef __SYS_TIMER_H__
#define __SYS_TIMER_H__

#include <c6x.h>
#include <tistdtypes.h>

void rt_hw_system_timer_init(void);

void rt_hw_system_timer_start(void);

#endif  /* __SYS_TIMER_H__ */

