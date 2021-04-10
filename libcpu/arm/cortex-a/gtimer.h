/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-30     huijie.feng  first version
 */

#ifndef __GTIMER_H__
#define __GTIMER_H__

#include <rtdef.h>

void gtimer_set_counter_frequency(rt_uint32_t value);
void gtimer_set_load_value(rt_uint32_t value);
rt_uint32_t gtimer_get_current_value(void);
rt_uint64_t gtimer_get_current_physical_value(void);
void gtimer_set_physical_compare_value(rt_uint64_t value);
rt_uint64_t gtimer_get_physical_compare_value(void);
void gtimer_set_control(rt_uint32_t value);
rt_uint32_t gtimer_get_control(void);

#endif

