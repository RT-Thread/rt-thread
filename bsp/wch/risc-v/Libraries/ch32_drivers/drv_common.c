/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-14     muaxiaohei   first version
 */

#include <rtthread.h>
#include "drv_common.h"
#include <board.h> /* for rt_hw_us_delay */

#define DBG_TAG    "drv.common"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint64_t total_delay_ticks, us_ticks, start, now, delta, reload;

    start = SysTick->CNT;
    reload = SysTick->CMP;
    us_ticks = SystemCoreClock / 8000000UL;
    total_delay_ticks = us * us_ticks;
    if (total_delay_ticks >= reload)
    {
        LOG_E("rt_hw_us_delay: the us parameter exceeds the maximum limit!");
    }

    do {
        now = SysTick->CNT;
        delta = start > now ? start - now : reload + start - now;
    } while(delta < total_delay_ticks);
}
