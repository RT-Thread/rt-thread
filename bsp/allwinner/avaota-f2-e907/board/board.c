/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"
#include "plic.h"

extern int rt_hw_tick_init(void);

void rt_hw_board_init(void)
{
    rt_hw_interrupt_init();
    v861_plic_init();
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    rt_hw_uart_print_dt();

#ifdef RT_USING_HEAP
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    rt_hw_tick_init();

    {
        unsigned long mie;
        __asm__ volatile("csrr %0, mie" : "=r"(mie));
        mie |= (1U << 11); /* MEIE for PLIC external interrupts */
        __asm__ volatile("csrw mie, %0" ::"r"(mie));
    }

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
