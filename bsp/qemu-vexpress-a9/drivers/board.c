/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 * 2018-11-22     Jesven     add rt_hw_spin_lock
 *                           add rt_hw_spin_unlock
 *                           add smp ipi init
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_timer.h"

#define SYS_CTRL                        __REG32(REALVIEW_SCTL_BASE)

extern void idle_wfi(void);
extern void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    /* initialize system heap */
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
#endif
}

