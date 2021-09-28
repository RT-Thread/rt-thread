/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-30     Kyle         First version
 */

#include <rtthread.h>

extern void rt_hw_board_init(void);
extern void rt_application_init(void);

#ifdef RT_USING_FINSH
extern int finsh_system_init(void);
extern void finsh_set_device(const char* device);
#endif

int main(void)
{
#ifdef RT_USING_HEAP
    extern void __heap_start__;
    extern void __heap_end__;
#endif

    rt_hw_board_init();
    rt_system_timer_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init(&__heap_start__, &__heap_end__);
#endif

    rt_system_scheduler_init();
    rt_application_init();

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device(FINSH_DEVICE_NAME);
#endif

    rt_thread_idle_init();
    rt_system_scheduler_start();

    return 0;
}
