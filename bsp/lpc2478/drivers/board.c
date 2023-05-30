/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <LPC24xx.h>
#include "board.h"

#define DATA_COUNT 14400000/RT_TICK_PER_SECOND  /* T0MR0 = delayInMs * (Fpclk / 1000); */

extern void rt_hw_serial_init(void);

/**
 * @addtogroup LPC2478
 */
/*@{*/

void rt_timer_handler(int vector, void* param)
{
    T0IR |= 0x01;           /* clear interrupt flag */
    rt_tick_increase();
    VICVectAddr = 0;        /* Acknowledge Interrupt */
}

/**
 * This function will init LPC2478 board
 */
void rt_hw_board_init(void)
{
#if defined(RT_USING_DEVICE) && defined(RT_USING_UART1)
    rt_hw_serial_init();
    rt_console_set_device("uart1");
#endif

    T0IR    = 0xff;
    T0TC    = 0;
    T0MCR   = 0x03;
    T0MR0   = (DATA_COUNT);

    rt_hw_interrupt_install(TIMER0_INT, rt_timer_handler, RT_NULL, "tick");
    rt_hw_interrupt_umask(TIMER0_INT);

    T0TCR = 0x01; //enable timer0 counter
}

/*@}*/
