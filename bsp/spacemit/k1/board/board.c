/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"

/* Defined in link.lds */
extern unsigned int __bss_end;

#define HEAP_BEGIN      ((void *)&__bss_end)
#define HEAP_END        ((void *)((rt_size_t)HEAP_BEGIN + KERNEL_HEAP_SIZE))

static void __rt_assert_handler(const char *ex_string, const char *func, rt_size_t line)
{
    rt_kprintf("\n(%s) assertion failed at function:%s, line number:%d \n", ex_string, func, line);
    while (1);
}

/* C entry point for the primary CPU, called from startup_gcc.S */
void primary_cpu_entry(void)
{
    rt_hw_interrupt_disable();
    rt_assert_set_hook(__rt_assert_handler);
    entry(); // Call RT-Thread kernel entry
}

/* This function is called by the kernel before the scheduler starts */
void rt_hw_board_init(void)
{
#ifdef RT_USING_HEAP
    /* Initialize the system heap */
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

    /*
     * Initialize hardware interrupts:
     */
    rt_hw_interrupt_init();

    /*
     * Initialize the UART driver for console output.
     * This function will handle pinctrl and sysctl initialization internally.
     */
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    /* Set the console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* Initialize auto-initialized components */
    rt_components_board_init();
#endif

}