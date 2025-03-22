/*
 * Copyright (c) 2024-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-9      Dyyt587      the first version
 */

#include "cpuusage.h"
//#ifdef RT_USING_CPU_USAGE
#if 1
static rt_tick_t pause_tick = 0;

/**
 * @brief pause usage measure
 * 
 * @note reduce scheduler time consuming
 */
void rt_usage_measure_pause(void)
{
    pause_tick = rt_tick_get();
}
/**
 * @brief start usage measure
 *
 * @param from wait to turn on
 * @param to turn to be
 */
void rt_usage_measure_start(struct rt_thread *from, struct rt_thread *to)
{
    /* to avoid scheduler time consuming */
    from->duration_tick += pause_tick - from->last_start_tick;

    to->last_start_tick = rt_tick_get(); 
}



#endif /* RT_USING_CPU_USAGE */