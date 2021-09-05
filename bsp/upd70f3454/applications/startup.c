/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2010-06-29     lgnq         for V850
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#include "CG_macrodriver.h"
#include "CG_system.h"
#include "CG_port.h"
#include "CG_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

extern int  rt_application_init(void);

#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char *device);
#endif

#ifdef RT_USING_HEAP
#ifdef __ICCV850__
#pragma section="RT_HEAP"
#endif
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __ICCV850__
    rt_system_heap_init(__segment_begin("RT_HEAP"), __segment_end("RT_HEAP"));
#endif
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init application */
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device("uart0");
#endif

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* init system setting */
    TAB0_Start();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}
