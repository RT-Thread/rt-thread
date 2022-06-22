/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-24     WangHuachen  the first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <dfs_fs.h>

#include "board.h"
#include "drv_timer.h"

#define ITERS_PER_USEC  (XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ / 4000000)
void rt_hw_us_delay(rt_uint32_t us)
{
    __asm__ __volatile__ (
        "push {r0,r1,r3} \n"
        "mov r0, %[usec] \n"
        "mov r1, %[iter] \n"
        "1: \n"
        "mov r3, r1 \n"
        "2: \n"
        "subs r3, r3, #0x1\n"
        "bne 2b \n"
        "subs r0, r0, #0x1 \n"
        "bne 1b \n"
        "pop {r0,r1,r3} \n"
        ::[iter] "r" (ITERS_PER_USEC), [usec] "r" (us)
        );
}

#ifdef RT_USING_CONSOLE

#include "drv_uart.h"
void rt_hw_serial_putc(const char c)
{
    UART_Registers *uart = (UART_Registers *)XPAR_PSU_UART_0_BASEADDR;
    if (c == '\n')
        rt_hw_serial_putc('\r');

    while ((uart->SR) & UART_SR_TXFULL);
    uart->FIFO = c;
}
void rt_hw_console_output(const char *str)
{
    while (*str)
    {
        rt_hw_serial_putc(*str++);
    }
}
#endif

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    /* initialize system heap */
#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}