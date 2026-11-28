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

/* rt_hw_uart_print_dt is declared in drv_uart.h */

extern int rt_hw_tick_init(void);

/*
 * SMP scheduler asserts rt_hw_interrupt_is_disabled() before posting a
 * context switch. The weak stub in irq.c always returns RT_FALSE, so provide
 * a real M-mode check (mstatus.MIE == 0 means IRQs disabled).
 */
rt_bool_t rt_hw_interrupt_is_disabled(void)
{
    unsigned long mstatus;

    __asm__ volatile("csrr %0, mstatus" : "=r"(mstatus));
    return (mstatus & (1UL << 3)) == 0;
}

void rt_hw_board_init(void)
{
    rt_hw_interrupt_init();
    v861_plic_init();
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* After console is up: show that UART came from embedded DTB. */
    rt_hw_uart_print_dt();

#ifdef RT_USING_HEAP
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    rt_hw_tick_init();

    {
        unsigned long mie;
        __asm__ volatile("csrr %0, mie" : "=r"(mie));
        mie |= (1U << 3);  /* MSIE for IPI */
        mie |= (1U << 11); /* MEIE for PLIC external interrupts */
        __asm__ volatile("csrw mie, %0" ::"r"(mie));
    }

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
