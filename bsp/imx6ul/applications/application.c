/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 */

#include <rtthread.h>

#include <sdk_version.h>
#include <ccm_pll.h>

void show_freq(void)
{
    rt_kprintf("CPU: %d MHz\n", get_main_clock(CPU_CLK)/1000000);
    rt_kprintf("DDR: %d MHz\n", get_main_clock(MMDC_CH0_AXI_CLK)/1000000);
    rt_kprintf("IPG: %d MHz\n", get_main_clock(IPG_CLK)/1000000);
}

void init_thread(void* parameter)
{
    rt_kprintf("Freescale i.MX6 Platform SDK %s\n", SDK_VERSION_STRING);
    show_freq();

    rt_components_init();
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init", init_thread, RT_NULL,
        1024, RT_THREAD_PRIORITY_MAX/3, 10);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}

