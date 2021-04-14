/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-12     Bluebear233  first implementation
 */
#include <rtconfig.h>
#include <rtthread.h>

int main(void)
{
#ifdef RT_USING_LWIP
    /* initialize eth interface */
    extern void rt_hw_nuc472_emac_init(void);
    rt_hw_nuc472_emac_init();
#endif /* RT_USING_LWIP */

    while(1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

