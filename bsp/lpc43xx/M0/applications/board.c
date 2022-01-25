/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2014-06-20     xiaonong     ported to LPC43xx
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"


/** M0 does not have SysTick so we have to use RIT timer for it... */
void RIT_OR_WWDT_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (LPC_RITIMER->CTRL & 0x01)
    {
        rt_tick_increase();
        LPC_RITIMER->CTRL |= 0x01;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

extern void SystemCoreClockUpdate(void);

/**
 * This function will initial LPC43xx board.
 */
void rt_hw_board_init()
{
    SystemCoreClockUpdate();

    /* Setup RIT timer. */
    LPC_RITIMER->MASK     = 0;
    LPC_RITIMER->COMPVAL  = SystemCoreClock / RT_TICK_PER_SECOND;
    /* Enable auto-clear. */
    LPC_RITIMER->CTRL    |= 1 << 1;
    /* Reset the counter as the counter is enabled after reset. */
    LPC_RITIMER->COUNTER  = 0;
    NVIC_SetPriority(M0_RITIMER_OR_WWDT_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
    NVIC_EnableIRQ(M0_RITIMER_OR_WWDT_IRQn);

    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /* init uart device */
    rt_hw_uart_init();

    /* setup the console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

