/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-14     aozima       first implementation for Nios II.
 */


#include <rthw.h>
#include <rtthread.h>

#include <stdio.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"

#include "uart.h"

extern int alt_irq_register (alt_u32 id,
                             void*   context,
                             void (*alt_isr_func)(void* isr_context, alt_u32 id) );

/**
 * @addtogroup NIOS_II
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 *
 */
void rt_hw_timer_handler(void * context,unsigned long id)
{
    void* base = (void*)TIMER_BASE;

    /* clear the interrupt */
    IOWR_ALTERA_AVALON_TIMER_STATUS (base, 0);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

void sysTick_config(void)
{
    void* base = (void*)TIMER_BASE;

    IOWR_ALTERA_AVALON_TIMER_CONTROL (base,
                                      ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
                                      ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
                                      ALTERA_AVALON_TIMER_CONTROL_START_MSK);

    alt_irq_register (TIMER_IRQ, NULL, rt_hw_timer_handler);
}

static void rt_hw_show_info(void)
{
    rt_kprintf("\r\n\r\n---------- board info ----------\r\n");
    rt_kprintf("ALT_DEVICE_FAMILY:    %s\r\n",ALT_DEVICE_FAMILY);
    rt_kprintf("ALT_CPU_ARCHITECTURE: %s\r\n",ALT_CPU_ARCHITECTURE);
    rt_kprintf("ALT_CPU_CPU_FREQ:     %uMHz\r\n",ALT_CPU_CPU_FREQ/1000000UL);
    rt_kprintf("memory size:          at 0x%08X 0x%08X byte\r\n",SDRAM_BASE,SDRAM_SPAN);
}

void rt_hw_board_init(void)
{
    rt_hw_uart_init();
    rt_console_set_device("uart");
    rt_hw_show_info();

    sysTick_config();
}

/*@}*/

